// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Widget/NBG_HUD.h"
#include "NBG_MegamanSystem.generated.h"

/**
 * 
 */
UCLASS()
class NOELDESBG_API ANBG_MegamanSystem : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	int32 CountPoint = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	UNBG_HUD* HUD;

public:
	void AddPoint(int32 _point);
	inline void SetHUD(UNBG_HUD* _HUD) { HUD = _HUD; };
};
