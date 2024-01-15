// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../Private/Items/NBG_ItemParent.h"
#include "../../NBG_HeroCharacter.h"
#include "HealthBoost.generated.h"

UCLASS()
class NOELDESBG_API AHealthBoost : public ANBG_ItemParent
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
	int32 HPRecovery = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value", meta = ( InstanceEditable))
	bool IsHPMedium;

	// Sets default values for this actor's properties
	AHealthBoost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
