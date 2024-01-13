// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_Spike.h"

// Sets default values
ANBG_Spike::ANBG_Spike()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ANBG_Spike::OnOverlapBegin);
	RootComponent = StaticMeshComponent;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANBG_Spike::BeginPlay()
{
	Super::BeginPlay();
	FString RowName = TEXT("SpikeDamage");
	Damage = GetDataTableValue(RowName);
}

void ANBG_Spike::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if (ANBG_HeroCharacter* other = Cast<ANBG_HeroCharacter>(OtherActor)) {
		other->GetDamage(Damage);
	}
}
