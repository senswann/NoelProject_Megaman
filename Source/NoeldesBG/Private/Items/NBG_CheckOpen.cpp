// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_CheckOpen.h"

// Sets default values
ANBG_CheckOpen::ANBG_CheckOpen()
{
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxCollision->InitBoxExtent(FVector(32.f, 32.f, 32.f)); // Définir les dimensions du cube
    RootComponent = BoxCollision;
    
    BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ANBG_CheckOpen::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ANBG_CheckOpen::BeginPlay()
{
	Super::BeginPlay();
}

void ANBG_CheckOpen::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (this && GetWorld())
    {
        GetWorldTimerManager().ClearTimer(TimerHandle);
        UE_LOG(LogTemp, Error, TEXT("Sucessfully cleared timer call!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to clear timer calls !"));
    }
}

void ANBG_CheckOpen::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (ANBG_Platform* other = Cast<ANBG_Platform>(OtherActor)) {
        if (BoxCollision) {
            BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            other->OpenPlatform();
            GetWorldTimerManager().SetTimer(TimerHandle, [this]() {
                if (this && IsValid(this) && this->BoxCollision && IsValid(this->BoxCollision))
                {
                    BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("I am indeed crashing !"));
                }
            }, 0.3, false);
        }
    }
}