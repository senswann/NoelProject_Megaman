// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Private/Items/NBG_ItemParent.h"
#include "GameFramework/ProjectileMovementComponent.h" 
#include "NBG_Projectiles.generated.h"

UCLASS()
class NOELDESBG_API ANBG_Projectiles : public ANBG_ItemParent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UProjectileMovementComponent* ProjectileMovementComponent;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 Dammage=0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	bool isBoss = false;
	// Sets default values for this actor's properties
	ANBG_Projectiles();

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
	bool EnsureDataTableValue();
};
