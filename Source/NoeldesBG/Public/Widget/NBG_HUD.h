// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "NBG_HUD.generated.h"

/**
 * 
 */
UCLASS()
class NOELDESBG_API UNBG_HUD : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 HP_Max=0;
	float HP = 0;

	int32 HP_Max_Boss=0;
	float HP_Boss=0;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* pointCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProgressBar* HP_Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProgressBar* HP_Slider_Boss;

	void AddPoint(int32 _points);
	void SetHP(int32 _hp);
	void SetHPBoss(int32 _hp);
	void SetHP_Max(int32 _hp);
	void SetHP_Max_Boss(int32 _hp);
};
