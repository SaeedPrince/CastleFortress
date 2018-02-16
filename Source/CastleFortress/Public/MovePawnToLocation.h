// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Reposition.h"
#include "MovePawnToLocation.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEFORTRESS_API UMovePawnToLocation : public UReposition
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AI|Movement")
		static UMovePawnToLocation* MovePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector Destination, const float AcceptableDistance, const float MoveInterval, const float EndTime);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface

protected:
	UFUNCTION()
		virtual void _MoveControl() override;
	UFUNCTION()
		virtual void _Finish() override;

private:
	const UObject* WorldContextObject;
};
