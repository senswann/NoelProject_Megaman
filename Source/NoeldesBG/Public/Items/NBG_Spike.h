// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Private/Items/NBG_ItemParent.h"
#include "../NBG_HeroCharacter.h"
#include "NBG_Spike.generated.h"

UCLASS(Blueprintable)
class NOELDESBG_API ANBG_Spike : public ANBG_ItemParent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 Damage=0;

public:	
	// Sets default values for this actor's properties
	ANBG_Spike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
