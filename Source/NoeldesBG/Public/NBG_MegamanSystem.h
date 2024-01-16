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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Value", meta = (AllowPrivateAccess = "true"))
	int32 CountPoint = 0;

	UNBG_HUD* HUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> MainMenu_Class;
	UUserWidget* MainMenu_W;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> StageSelection_Class;
	UUserWidget* StageSelection_W;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> GameOver_Class;
	UUserWidget* GameOver_W;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> Menu_Class;
	UUserWidget* Menu_W;

	static int32 indexLevel;

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
	void GameOver();

	UFUNCTION(BlueprintCallable)
	void StageSelection();

	UFUNCTION(BlueprintCallable)
	inline int32 GetPoints() { return CountPoint; };

	UFUNCTION(BlueprintCallable)
	void SetUIOnlyInputMode();

	UFUNCTION(BlueprintCallable)
	void SetGameOnlyInputMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
