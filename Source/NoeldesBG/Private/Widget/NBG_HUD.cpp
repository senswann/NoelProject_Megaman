// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NBG_HUD.h"
#include "Components/TextBlock.h"

void UNBG_HUD::AddPoint(int32 _points) {
	pointCount->SetText(FText::FromString(FString::FromInt(_points)));
}

void UNBG_HUD::SetHP(int32 _hp) {
	UE_LOG(LogTemp, Warning, TEXT("HP Set"));
	HP = (static_cast<float>(_hp) / HP_Max);
	UE_LOG(LogTemp, Warning, TEXT("Ma variable float : %f"), HP);
	HP_Slider->SetPercent(HP);
}

void UNBG_HUD::SetHPBoss(int32 _hp) {
	UE_LOG(LogTemp, Warning, TEXT("HP Set"));
	HP_Boss = (static_cast<float>(_hp) / HP_Max_Boss);
	HP_Slider_Boss->SetPercent(HP_Boss);
}

void UNBG_HUD::SetHP_Max(int32 _hp) {
	HP_Max = _hp; 
	SetHP(HP_Max);
}

void UNBG_HUD::SetHP_Max_Boss(int32 _hp) {
	HP_Max_Boss = _hp;
	SetHPBoss(HP_Max_Boss);
}