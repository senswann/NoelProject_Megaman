// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBG_StatsStruct.generated.h"


USTRUCT(BlueprintType)
struct FNBG_StatsStruct : public FTableRowBase
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Value=0;
	
};
