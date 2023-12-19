// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_Platform.h"

#define PBool(value) (*FString((value)?"True":"False"))
#define PName(value) (*((IsValid(value))?value->GetName():FString(value == nullptr ? "nullptr":"invalidObject")))
#define POwnerName(value) (*((IsValid(value))?value->GetOwner()->GetName():FString(value == nullptr ? "nullptr":"invalidComponent")))
#define PEnum(value) (*UEnum::GetValueAsString(value))
#define IPName(value) ( *( (value != nullptr && IsValid(value->_getUObject())) ? value->_getUObject()->GetName() : FString(value == nullptr ? "nullptr":"invalidObject") ) )

// Sets default values
ANBG_Platform::ANBG_Platform()
{
    // Create the static mesh component and set it as the root component
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = StaticMeshComponent;

    InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("MyInterpToMovementComponent"));
    if (InterpToMovementComponent)
    {
        // Set properties for the movement
        InterpToMovementComponent->UpdatedComponent = RootComponent; // Assign the root component of your actor as the component to move
    }
}

// Called when the game starts or when spawned
void ANBG_Platform::BeginPlay()
{
	Super::BeginPlay();
    if (InterpToMovementComponent)
    {
        // Set properties for the movement
        InterpToMovementComponent->UpdatedComponent = RootComponent; // Assign the root component of your actor as the component to move
        InterpToMovementComponent->Activate();
    }
}

void ANBG_Platform::PreInitializeComponents()
{
    UE_LOG(LogTemp, Warning, TEXT("PreInitializeComponents is %s"), PName(DT_ValueInGame));

    EnsureDataTableValue();
    Super::PreInitializeComponents();
}

#if WITH_EDITOR
void ANBG_Platform::PostInitializeComponents()
{
    UE_LOG(LogTemp, Warning, TEXT("PostInitializeComponents is %s"), PName(DT_ValueInGame));

    EnsureDataTableValue();
    Super::PostInitializeComponents();
}

void ANBG_Platform::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("PostEditChangeProperty is %s"), PName(DT_ValueInGame));
    EnsureDataTableValue();
    Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

bool ANBG_Platform::Create2Point()
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
