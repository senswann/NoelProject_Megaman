// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Public/NBG_StatsStruct.h"
#include "NBG_ItemParent.generated.h"

class UDataTable;
UCLASS()
class ANBG_ItemParent : public AActor
{
	GENERATED_BODY()
	
public:	
	//pour stocker la référence a la DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
    UDataTable* DT_ValueInGame;
	// Sets default values for this actor's properties
	ANBG_ItemParent();

protected:
	virtual void BeginPlay() override;

public:	
	int32 GetDataTableValue(const FString RowName);
	// Called when the game starts or when spawned
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
