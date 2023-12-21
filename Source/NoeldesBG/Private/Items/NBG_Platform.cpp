// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_Platform.h"

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
        InterpToMovementComponent->UpdatedComponent = RootComponent;
        /*InterpToMovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;
        InterpToMovementComponent->bAutoActivate = true;
        InterpToMovementComponent->bAllowConcurrentTick = true;*/
    }
    Locations.Init(FVector(), 2);
}

// Called when the game starts or when spawned
void ANBG_Platform::BeginPlay()
{
    Super::BeginPlay();
    /*if (InterpToMovementComponent)
    {
        TArray<FInterpControlPoint> InterpArray;
        InterpArray.Add(FInterpControlPoint(Locations[0], true));
        InterpArray.Add(FInterpControlPoint(Locations[1], true));

        InterpToMovementComponent->ControlPoints = InterpArray;
        InterpToMovementComponent->Duration = Duration;
        InterpToMovementComponent->FinaliseControlPoints();
        InterpToMovementComponent->Activate();
    }*/
}

void ANBG_Platform::OpenPlatform()
{
        FRotator tmpRotation;
    if (OpenPlatformBool) {
        tmpRotation = FRotator(0.0f, -40.f, 0.0f);
    }else{
        tmpRotation = FRotator(0.0f, 40.f, 0.0f);
    }
    StaticMeshComponent->AddLocalRotation(tmpRotation);
    OpenPlatformBool = !OpenPlatformBool;
}
