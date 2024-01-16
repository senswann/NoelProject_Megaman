// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Bonus/HealthBoost.h"

// Sets default values
AHealthBoost::AHealthBoost()
{
	// Create the static mesh component and set it as the root component
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealthBoost::OnOverlapBegin);
	BoxCollision->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AHealthBoost::BeginPlay()
{
	Super::BeginPlay();
	FString RowName = (IsHPMedium? TEXT("MediumLifeBonus") : TEXT("LowLifeBonus"));
	HPRecovery = GetDataTableValue(RowName);
}

void AHealthBoost::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if (ANBG_HeroCharacter* other = Cast<ANBG_HeroCharacter>(OtherActor)) {
		other->SetHP(HPRecovery);
		Destroy();
	}
}

