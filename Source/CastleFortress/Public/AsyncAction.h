// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncActionOutputPin);

/**
 * 
 */
UCLASS()
class CASTLEFORTRESS_API UAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
		FAsyncActionOutputPin Start;
	UPROPERTY(BlueprintAssignable)
		FAsyncActionOutputPin Update;
	UPROPERTY(BlueprintAssignable)
		FAsyncActionOutputPin Finish;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AI|Action")
		static UAsyncAction* AsyncAction(const UObject* WorldContextObject, const float UpdateInterval, const float EndTime);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface

private:

	UFUNCTION()
		void _Start();
	UFUNCTION()
		void _Update();
	UFUNCTION()
		void _Finish();

	const UObject* WorldContextObject;
	bool Active;
	float UpdateInterval;
	float EndTime;
	FTimerHandle TimerUpdate;

};
