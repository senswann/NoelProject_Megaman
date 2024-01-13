// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Widget/NBG_HUD.h"
#include "Widget/NBG_Menu.h"
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

	UNBG_HUD* HUD;

    UNBG_Menu* Menu_W;

	bool visibility = false;

public:
	void AddPoint(int32 _point);
	inline void SetHUD(UNBG_HUD* _HUD) { HUD = _HUD; };
	inline void SetMenu(UNBG_Menu* _Menu_W) { Menu_W = _Menu_W; Menu(); };

	UFUNCTION(BlueprintCallable)
	void Menu();

	UFUNCTION(BlueprintCallable)
	void Load(int32 _index);

	UFUNCTION(BlueprintCallable)
	void Quit();

	UFUNCTION(BlueprintCallable)
	void SetUIOnlyInputMode();

	UFUNCTION(BlueprintCallable)
	void SetGameOnlyInputMode();
};
