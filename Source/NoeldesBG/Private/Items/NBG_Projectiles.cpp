// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_Projectiles.h"

#define PBool(value) (*FString((value)?"True":"False"))
#define PName(value) (*((IsValid(value))?value->GetName():FString(value == nullptr ? "nullptr":"invalidObject")))
#define POwnerName(value) (*((IsValid(value))?value->GetOwner()->GetName():FString(value == nullptr ? "nullptr":"invalidComponent")))
#define PEnum(value) (*UEnum::GetValueAsString(value))
#define IPName(value) ( *( (value != nullptr && IsValid(value->_getUObject())) ? value->_getUObject()->GetName() : FString(value == nullptr ? "nullptr":"invalidObject") ) )

// Sets default values
ANBG_Projectiles::ANBG_Projectiles()
{
    SetLifeSpan(1.f);
    // Create the static mesh component and set it as the root component
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    RootComponent = StaticMeshComponent;

    // Create and initialize the projectile movement component
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(StaticMeshComponent);

    ProjectileMovementComponent->bRotationFollowsVelocity = false;
    ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void ANBG_Projectiles::BeginPlay()
{
    Super::BeginPlay();
    FString RowName;

    if (GetOwner()) {
        FString OwnerClassName = Owner->GetClass()->GetName();

        // Use the class name in a switch statement
        if (OwnerClassName == "ANBG_HeroCharacter")
        {
            RowName = TEXT("DamageJoueur");
            Dammage = GetDataTableValue(RowName);
        }
        else if (OwnerClassName == "ANBG_AiSimple")
        {
            RowName = TEXT("SimpleEnnemiDamage");
            Dammage = GetDataTableValue(RowName);
        }
        else {}
        // Désactiver les collisions
        if (StaticMeshComponent)
        {
            StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
        // Réactiver les collisions après un délai de 0.1 seconde
        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, [this]()
            {
                StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            }, 0.1f, false);
    }
}

void ANBG_Projectiles::PreInitializeComponents()
{
    UE_LOG(LogTemp, Warning, TEXT("PreInitializeComponents is %s"), PName(DT_ValueInGame));

    EnsureDataTableValue();
    Super::PreInitializeComponents();
}

#if WITH_EDITOR
void ANBG_Projectiles::PostInitializeComponents()
{
    UE_LOG(LogTemp, Warning, TEXT("PostInitializeComponents is %s"), PName(DT_ValueInGame));

    EnsureDataTableValue();
    Super::PostInitializeComponents();
}

void ANBG_Projectiles::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("PostEditChangeProperty is %s"), PName(DT_ValueInGame));
    EnsureDataTableValue();
    Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

bool ANBG_Projectiles::EnsureDataTableValue()
{
    if (DT_ValueInGame)
    {
        FString RowName = TEXT("ShootSpeed");
        float ValueFromDataTable = static_cast<float>(GetDataTableValue(RowName));
        ProjectileMovementComponent->InitialSpeed = ValueFromDataTable;
        ProjectileMovementComponent->MaxSpeed = ValueFromDataTable;
        return true;
    }
    return false;
}