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
	float HP=0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* pointCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProgressBar* HP_Slider;

	void AddPoint(int32 _points);
	void SetHP(int32 _hp);
	void SetHP_Max(int32 _hp);
};
