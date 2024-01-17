// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_BigProjectile.h"

#define PBool(value) (*FString((value)?"True":"False"))
#define PName(value) (*((IsValid(value))?value->GetName():FString(value == nullptr ? "nullptr":"invalidObject")))
#define POwnerName(value) (*((IsValid(value))?value->GetOwner()->GetName():FString(value == nullptr ? "nullptr":"invalidComponent")))
#define PEnum(value) (*UEnum::GetValueAsString(value))
#define IPName(value) ( *( (value != nullptr && IsValid(value->_getUObject())) ? value->_getUObject()->GetName() : FString(value == nullptr ? "nullptr":"invalidObject") ) )

// Sets default values
ANBG_BigProjectile::ANBG_BigProjectile()
{
    // Create the static mesh component and set it as the root component
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    RootComponent = MeshComponent;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ANBG_BigProjectile::OnOverlapBegin);

    // Create and initialize the projectile movement component
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(MeshComponent);

    ProjectileMovementComponent->bRotationFollowsVelocity = false;
    ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void ANBG_BigProjectile::BeginPlay()
{
    Super::BeginPlay();
    FString RowName;

    if (GetOwner()) {
        FString OwnerClassName = Owner->GetClass()->GetName();
        UE_LOG(LogTemp, Warning, TEXT("Class : %s"), *OwnerClassName);
        // Use the class name in a switch statement
        if (OwnerClassName == "BP_NBG_HeroCharacter_C")
        {
            UE_LOG(LogTemp, Warning, TEXT("HERO"));
            RowName = TEXT("DamageJoueur");
            Dammage = GetDataTableValue(RowName);
        }
        else if (OwnerClassName == "BP_AiBase_Simple_C")
        {
            UE_LOG(LogTemp, Warning, TEXT("SIMPLE"));
            RowName = TEXT("SimpleEnnemiDamage");
            Dammage = GetDataTableValue(RowName);
        }
        else if (OwnerClassName == "BP_AiBase_Complex_C")
        {
            UE_LOG(LogTemp, Warning, TEXT("COMPLEX"));
            RowName = TEXT("ComplexEnnemiDmg");
            Dammage = GetDataTableValue(RowName);
        }
        else if (OwnerClassName == "BP_AiBase_Boss_C")
        {
            UE_LOG(LogTemp, Warning, TEXT("BOSS"));
            RowName = TEXT("BossEnnemiDamage");
            Dammage = GetDataTableValue(RowName);
        }
        else {}
    }
}

int32 ANBG_BigProjectile::GetDataTableValue(const FString RowName)
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

void ANBG_BigProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    isCailloux = true;
    UE_LOG(LogTemp, Error, TEXT("Overlap: %s"), *OtherActor->GetName())
}

void ANBG_BigProjectile::PreInitializeComponents()
{
    UE_LOG(LogTemp, Warning, TEXT("PreInitializeComponents is %s"), PName(DT_ValueInGame));

    EnsureDataTableValue();
    Super::PreInitializeComponents();
}

#if WITH_EDITOR
void ANBG_BigProjectile::PostInitializeComponents()
{
    UE_LOG(LogTemp, Warning, TEXT("PostInitializeComponents is %s"), PName(DT_ValueInGame));

    EnsureDataTableValue();
    Super::PostInitializeComponents();
}

void ANBG_BigProjectile::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("PostEditChangeProperty is %s"), PName(DT_ValueInGame));
    EnsureDataTableValue();
    Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

bool ANBG_BigProjectile::EnsureDataTableValue()
{
    if (DT_ValueInGame)
    {
        FString RowName = (isBoss ? TEXT("BossProjectileSpeed") : TEXT("ProjectileSpeed"));
        float ValueFromDataTable = static_cast<float>(GetDataTableValue(RowName));
        ProjectileMovementComponent->InitialSpeed = ValueFromDataTable;
        ProjectileMovementComponent->MaxSpeed = ValueFromDataTable;
        return true;
    }
    return false;
}

