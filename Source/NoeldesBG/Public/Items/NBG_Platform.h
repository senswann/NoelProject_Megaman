// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InterpToMovementComponent.h"
#include "../../Private/Items/NBG_ItemParent.h"
#include "NBG_Platform.generated.h"

UCLASS()
class NOELDESBG_API ANBG_Platform : public ANBG_ItemParent
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInterpToMovementComponent* InterpToMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInterpToMovementComponent* InterpToMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInterpToMovementComponent* InterpToMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInterpToMovementComponent* InterpToMovementComponent;
public:	
	// Sets default values for this actor's properties
	ANBG_Platform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents();

#if WITH_EDITOR
	//Handle UDataTable after first compile of project
	virtual void PostInitializeComponents() override;
	//Handle UDataTable after property change
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	bool Create2Point();

};
