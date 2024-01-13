// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NBG_ItemParent.h"

// Sets default values
ANBG_ItemParent::ANBG_ItemParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANBG_ItemParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANBG_ItemParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ANBG_ItemParent::GetDataTableValue(const FString RowName) {
	if (DT_ValueInGame != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("DataTable Valid"));
		bool bSuccess = false;

		FName name = FName(RowName);
		FNBG_StatsStruct* tmp_RowValue = DT_ValueInGame->FindRow<FNBG_StatsStruct>(name, "", bSuccess);
		//UE_LOG(LogTemp, Warning, TEXT("Row Value Found: %d"), tmp_RowValue->Value);
		if (tmp_RowValue != nullptr) {
			return tmp_RowValue->Value;
		}
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("DataTable Not Valid"));
	}
	return 0;
}

