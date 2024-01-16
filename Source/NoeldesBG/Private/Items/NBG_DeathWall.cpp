// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_DeathWall.h"
// Sets default values
ANBG_DeathWall::ANBG_DeathWall()
{
    // Create the static mesh component and set it as the root component
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = StaticMeshComponent;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxCollision->InitBoxExtent(FVector(32.f, 32.f, 32.f));
    BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ANBG_DeathWall::OnOverlapBegin);
    BoxCollision->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ANBG_DeathWall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    UE_LOG(LogTemp, Warning, TEXT("DeathWall"));
    if (ANBG_HeroCharacter* other = Cast<ANBG_HeroCharacter>(OtherActor)) {
        other->Death();
    }
}
