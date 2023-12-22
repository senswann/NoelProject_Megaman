// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Bonus/NBG_PointCoins.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANBG_PointCoins::ANBG_PointCoins()
{
	// Create the static mesh component and set it as the root component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ANBG_PointCoins::OnOverlapBegin);
	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void ANBG_PointCoins::BeginPlay()
{
	Super::BeginPlay();
	FString RowName = TEXT("PointCollectible");
	Points = GetDataTableValue(RowName);
}

void ANBG_PointCoins::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if (ANBG_HeroCharacter* other = Cast<ANBG_HeroCharacter>(OtherActor)) {
		if (ANBG_MegamanSystem* _GameMode = Cast<ANBG_MegamanSystem>(UGameplayStatics::GetGameMode(GetWorld()))) {
			_GameMode->AddPoint(Points);
			Destroy();
		}
	}
}

