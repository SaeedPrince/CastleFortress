// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FacePawnToLocation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFacePawnToLocationOutputPin, bool, Success);

/**
 * 
 */
UCLASS()
class CASTLEFORTRESS_API UFacePawnToLocation : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
		FFacePawnToLocationOutputPin Finished;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AI|Rotation")
		static UFacePawnToLocation* FacePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector ActorLocation, const float AcceptableAngle, const float TurnInterval, const float EndTime);

	/*
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AI|Rotation")
		static UFacePawnToLocation* FacePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector ActorLocation, const float Acc
	*/

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface

private:

	UFUNCTION()
		void _TurnControl();
	UFUNCTION()
		void _Finish();
	UFUNCTION()
		bool _IsPawnFacingToActor();

	const UObject* WorldContextObject;
	bool Active;
	bool Okay;
	APawn* Pawn;
	FVector ActorLocation;
	float TurnInterval;
	float EndTime;
	float AcceptableAngle;
	FTimerHandle TimerTurnControl;

};
