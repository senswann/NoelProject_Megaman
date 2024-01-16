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

void ANBG_CheckOpen::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (ANBG_Platform* other = Cast<ANBG_Platform>(OtherActor)) {;
        BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        other->OpenPlatform();
        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, [this]() {
            BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            }, 0.5f, false);
    }
}