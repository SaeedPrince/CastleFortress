// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CaladanLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEFORTRESS_API UCaladanLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Math")
	static float IntPowerOfFloat(const float fltNumber, const int intNumber);

	
};
