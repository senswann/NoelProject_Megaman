// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../../Public/NBG_StatsStruct.h"
#include "GameFramework/ProjectileMovementComponent.h" 
#include "NBG_BigProjectile.generated.h"

UCLASS()
class NOELDESBG_API ANBG_BigProjectile : public APawn
{
	GENERATED_BODY()
	
	//pour stocker le pointeur de la DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
	UDataTable* DT_ValueInGame;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 Dammage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
	bool isBoss = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
	bool isCailloux = false;
	// Sets default values for this actor's properties
	ANBG_BigProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 GetDataTableValue(const FString RowName);

	virtual void PreInitializeComponents();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#if WITH_EDITOR
	//Handle UDataTable after first compile of project
	virtual void PostInitializeComponents() override;
	//Handle UDataTable after property change
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	bool EnsureDataTableValue();
};
