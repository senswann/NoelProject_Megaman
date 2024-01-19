// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "NBG_Platform.h"
#include "NBG_CheckOpen.generated.h"

UCLASS()
class NOELDESBG_API ANBG_CheckOpen : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* BoxCollision;

	FTimerHandle TimerHandle;
public:	
	// Sets default values for this actor's properties
	ANBG_CheckOpen();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay
	(
		const EEndPlayReason::Type EndPlayReason
	) override;
};
