// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Reposition.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRepositionOutputPin, bool, Success);

/**
 * 
 */
UCLASS()
class CASTLEFORTRESS_API UReposition : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
		FRepositionOutputPin Finished;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AI|Movement")
		static UReposition* Reposition(const UObject* WorldContextObject, APawn* Pawn, FVector Destination, const float AcceptableAngle, const float AcceptableDistance, const float TurnInterval, const float MoveInterval, const float EndTime);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface

private:

	UFUNCTION()
		bool _IsPawnFacingToActor();
	UFUNCTION()
		bool _IsPawnCloseToActor();
	UFUNCTION()
		float _AngleBetweenVecs(FVector DistanceVector, FVector DirectionVector);
	UFUNCTION()
		FVector _PawnDirection();
	UFUNCTION()
		void _TurnControl();
	UFUNCTION()
		void _MoveControl();
	UFUNCTION()
		void _DoneControl();
	UFUNCTION()
		void _Finish();
	UFUNCTION()
		float _ClockWise();
	UFUNCTION()
		void _TurnOnePoint(float Value);
	UFUNCTION()
		void _MoveOnePoint();

	const UObject* WorldContextObject;
	bool Active;
	bool faceOkay;
	bool placeOkay;
	bool Okay;
	APawn* Pawn;
	FVector Destination;
	float TurnInterval;
	float MoveInterval;
	float EndTime;
	float AcceptableAngle;
	float AcceptableDistance;
	FTimerHandle TimerTurnControl;
	FTimerHandle TimerMoveControl;
	FTimerHandle TimerDoneControl;
};
