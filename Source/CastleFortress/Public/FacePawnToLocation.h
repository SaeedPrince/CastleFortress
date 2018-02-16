// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Reposition.h"
#include "FacePawnToLocation.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEFORTRESS_API UFacePawnToLocation : public UReposition
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AI|Rotation")
		static UFacePawnToLocation* FacePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector Destination, const float AcceptableAngle, const float TurnInterval, const float EndTime);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface

protected:
	UFUNCTION()
		virtual void _TurnControl() override;
	UFUNCTION()
		virtual void _Finish() override;
private:
	const UObject* WorldContextObject;

};
