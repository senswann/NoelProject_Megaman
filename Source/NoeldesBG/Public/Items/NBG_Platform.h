// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/BoxComponent.h"
#include "../../Private/Items/NBG_ItemParent.h"
#include "NBG_Platform.generated.h"

UCLASS()
class NOELDESBG_API ANBG_Platform : public ANBG_ItemParent
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* ParentMeshForInterp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent2;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInterpToMovementComponent* InterpToMovementComponent;
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value")
	bool OpenPlatformBool = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (MakeEditWidget, ExposeOnSpawn, InstanceEditable))
    TArray<FVector> Locations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value")
	float Duration = 1.f;

	void OpenPlatform();
	// Sets default values for this actor's properties
	ANBG_Platform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
