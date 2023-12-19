// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NBG_HUD.h"
#include "Components/TextBlock.h"

void UNBG_HUD::AddPoint(int32 _points) {
	pointCount->SetText(FText::FromString(FString::FromInt(_points)));
}

void UNBG_HUD::SetHP(int32 _points) {
	FString text = (FString::FromInt(_points)) + "/" + (FString::FromInt(HP_Max));
	HP->SetText(FText::FromString(text));
}

void UNBG_HUD::SetHP_Max(int32 _hp) {
	HP_Max = _hp; 
	SetHP(HP_Max);
}