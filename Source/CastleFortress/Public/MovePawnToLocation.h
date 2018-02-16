// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MovePawnToLocation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovePawnToLocationOutputPin, bool, Success);

/**
 * 
 */
UCLASS()
class CASTLEFORTRESS_API UMovePawnToLocation : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
		FMovePawnToLocationOutputPin Finished;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AI|Movement")
		static UMovePawnToLocation* MovePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector ActorLocation, const float AcceptableDistance, const float MoveInterval, const float EndTime);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface

private:

	UFUNCTION()
		bool _IsPawnCloseToActor();
	UFUNCTION()
		void _MoveControl();
	UFUNCTION()
		void _Finish();
	UFUNCTION()
		void _MoveOnePoint();

	const UObject* WorldContextObject;
	bool Active;
	bool Okay;
	APawn* Pawn;
	FVector ActorLocation;
	float MoveInterval;
	float EndTime;
	float AcceptableDistance;
	FTimerHandle TimerMoveControl;
	
};
