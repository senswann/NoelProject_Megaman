// Fill out your copyright notice in the Description page of Project Settings.


#include "NBG_MegamanSystem.h"

void ANBG_MegamanSystem::AddPoint(int32 _point){
	CountPoint += _point;
	HUD->AddPoint(CountPoint);
}
