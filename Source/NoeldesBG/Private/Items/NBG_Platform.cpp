// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_Platform.h"

// Sets default values
ANBG_Platform::ANBG_Platform()
{
    Locations.Init(FVector(), 2);
    // Create the static mesh component and set it as the root component
    ParentMeshForInterp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = ParentMeshForInterp;
    StaticMeshComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent2"));
    StaticMeshComponent2->AttachToComponent(ParentMeshForInterp, FAttachmentTransformRules::KeepRelativeTransform);

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxCollision->InitBoxExtent(FVector(32.f, 32.f, 32.f));
    BoxCollision->AttachToComponent(ParentMeshForInterp, FAttachmentTransformRules::KeepRelativeTransform);

    InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("MyInterpToMovementComponent"));
    if (InterpToMovementComponent)
    {
        // Set properties for the movement
        InterpToMovementComponent->UpdatedComponent = RootComponent;
        InterpToMovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;
        InterpToMovementComponent->bAutoActivate = true;
        InterpToMovementComponent->bSweep = false;
        InterpToMovementComponent->Velocity = FVector(0.5f, 0.5f, 0.5f);
    }
}

// Called when the game starts or when spawned
void ANBG_Platform::BeginPlay()
{
    Super::BeginPlay();
    if (InterpToMovementComponent)
    {
        FString RowName = TEXT("PlatformSpeed");
        float ValueFromDataTable = static_cast<float>(GetDataTableValue(RowName));
        Duration = ValueFromDataTable;
        TArray<FInterpControlPoint> InterpArray;
        InterpArray.Add(FInterpControlPoint(Locations[0], true));
        InterpArray.Add(FInterpControlPoint(Locations[1], true));

        InterpToMovementComponent->ControlPoints = InterpArray;
        InterpToMovementComponent->Duration = Duration;
        InterpToMovementComponent->FinaliseControlPoints();
        InterpToMovementComponent->Activate();
    }
}

void ANBG_Platform::OpenPlatform()
{
    FRotator tmpRotation;
    if (OpenPlatformBool) {
        BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        tmpRotation = FRotator(0.f, 0.f, 90.f);
    }else{
        BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        tmpRotation = FRotator(0.f, 0.f, -90.f);
    }
    StaticMeshComponent2->AddLocalRotation(tmpRotation);
    OpenPlatformBool = !OpenPlatformBool;
}
