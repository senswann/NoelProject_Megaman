// Fill out your copyright notice in the Description page of Project Settings.


#include "NBG_HeroCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Items/NBG_Projectiles.h"
#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
ANBG_HeroCharacter::ANBG_HeroCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 90.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//creation de l'arrow dee shoot
	ShootArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootArrowComponent")); // Créer le composant Arrow
	ShootArrowComponent->SetupAttachment(GetCapsuleComponent());
	ShootArrowComponent->SetRelativeLocationAndRotation(FVector(70.f, 0.f, 50.f), FRotator(0.f, 0.f, 0.f));

	//creation de la capsule de colision
	CapsuleColision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleColision")); // Créer la nouvelle CapsuleComponent
	CapsuleColision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CapsuleColision->SetupAttachment(RootComponent);
	CapsuleColision->InitCapsuleSize(40.f, 95.f);
	CapsuleColision->OnComponentBeginOverlap.AddDynamic(this, &ANBG_HeroCharacter::OnOverlapBegin);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

int32 ANBG_HeroCharacter::GetDataTableValue(const FString RowName)
{
	if (DT_ValueInGame != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("DataTable Valid"));
		bool bSuccess = false;

		FName name = FName(RowName);
		FNBG_StatsStruct* tmp_RowValue = DT_ValueInGame->FindRow<FNBG_StatsStruct>(name, "", bSuccess);
		UE_LOG(LogTemp, Warning, TEXT("Row Value Found: %d"), tmp_RowValue->Value);
		if (tmp_RowValue != nullptr) {
			return tmp_RowValue->Value;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("DataTable Not Valid"));
	}
	return 0;
}

// Called when the game starts or when spawned
void ANBG_HeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FString RowName = TEXT("VieJoueur");
	HP = HP_Max = GetDataTableValue(RowName);

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		if (GetWorld())
		{
			// Créer une instance de votre widget HUD
			HUD = CreateWidget<UNBG_HUD>(PlayerController, HUD_Class);

			if (HUD)
			{
				// Ajouter le widget à la vue (viewport)
				HUD->AddToViewport();
				UE_LOG(LogTemp, Warning, TEXT("Valeur HP: %d"), HP_Max);
				HUD->SetHP_Max(HP_Max);

				if (ANBG_MegamanSystem* _GameMode = Cast<ANBG_MegamanSystem>(UGameplayStatics::GetGameMode(GetWorld()))) {
					_GameMode->SetHUD(HUD);
				}
			}
		}
	}

}

//////////////////////////////////////////////////////////////////////////
// Input

void ANBG_HeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANBG_HeroCharacter::IA_Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANBG_HeroCharacter::IA_Look);
		
		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ANBG_HeroCharacter::IA_Shoot);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANBG_HeroCharacter::IA_Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ANBG_HeroCharacter::IA_Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ANBG_HeroCharacter::IA_Shoot(const FInputActionValue& Value)
{
	UWorld* World = GetWorld();
	if (Controller != nullptr){
		FVector ArrowLocation = ShootArrowComponent->GetComponentLocation();
		FRotator ArrowRotation = ShootArrowComponent->GetComponentRotation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(ArrowLocation);
		SpawnTransform.SetRotation(ArrowRotation.Quaternion());

		ANBG_Projectiles* TmpProjectile = World->SpawnActor<ANBG_Projectiles>(ProjectileClass, SpawnTransform);
		if (TmpProjectile){
			TmpProjectile->SetOwner(this);
		}
	}
}

void ANBG_HeroCharacter::Invicibility(){
	UE_LOG(LogTemp, Warning, TEXT("Invicible"));
	IsInvicible = true;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this](){
			UE_LOG(LogTemp, Warning, TEXT("Not Invicible"));
			IsInvicible = false;
		}, 1.5f, false);
}

void ANBG_HeroCharacter::SetHP(int32 _hp)
{
	UE_LOG(LogTemp, Warning, TEXT("Dmg : %d"), _hp);
	if ((_hp + HP) > 100) {
		HP = HP_Max;
	}
	else {
		HP += _hp;
	}
	HUD->SetHP(HP);
}

void ANBG_HeroCharacter::GetDamage(int32 _dmg)
{
	if (!IsInvicible) {
		if ((HP- _dmg) <= 0) {
			HP = 0;
		}
		else {
			HP -= _dmg;
		}
		Invicibility();
		HUD->SetHP(HP);
	}
}

void ANBG_HeroCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if (ANBG_Projectiles* other = Cast<ANBG_Projectiles>(OtherActor)) {
		GetDamage(other->Dammage);
	}
}