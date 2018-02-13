// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MiniTimer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMiniTimerOutputPin);

/**
 * 
 */
UCLASS()
class CASTLEFORTRESS_API UMiniTimer : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
		FMiniTimerOutputPin Update;
	UPROPERTY(BlueprintAssignable)
		FMiniTimerOutputPin Finished;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Timer|Mini-Timer")
		static UMiniTimer* MiniTimer(const UObject* WorldContextObject, const float TimerInterval, const float TimerDuration);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface

private:
	UFUNCTION()
		void _Update();
	UFUNCTION()
		void _Finish();

	const UObject* WorldContextObject;
	bool Active;
	FTimerHandle Timer;
	float TimerInterval;
	float TimerDuration;

};
