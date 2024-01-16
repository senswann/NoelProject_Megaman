// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../NBG_HeroCharacter.h"
#include "Components/BoxComponent.h"
#include "NBG_DeathWall.generated.h"

UCLASS()
class NOELDESBG_API ANBG_DeathWall : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* BoxCollision;
public:	
	// Sets default values for this actor's properties
	ANBG_DeathWall();

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
