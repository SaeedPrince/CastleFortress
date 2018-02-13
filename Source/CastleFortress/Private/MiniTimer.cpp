// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniTimer.h"

UMiniTimer* UMiniTimer::MiniTimer(const UObject* WorldContextObject, const float TimerInterval, const float TimerDuration)
{
	UMiniTimer* Node = NewObject<UMiniTimer>();
	Node->WorldContextObject = WorldContextObject;
	Node->TimerDuration = TimerDuration;
	Node->TimerInterval = TimerInterval;
	return Node;
}

void UMiniTimer::Activate()
{
	if (nullptr == WorldContextObject)
	{
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject. Cannot execute MiniTimer."), ELogVerbosity::Error);
		return;
	}
	if (Active)
	{
		FFrame::KismetExecutionMessage(TEXT("MiniTimer is already running."), ELogVerbosity::Warning);
		return;
	}
	if (TimerDuration <= 0.0f)
	{
		FFrame::KismetExecutionMessage(TEXT("Minitimer's TimerDuration cannot be less or equal to 0."), ELogVerbosity::Warning);
		return;
	}
	if (TimerInterval <= 0.0f)
	{
		FFrame::KismetExecutionMessage(TEXT("Minitimer's TimerInterval cannot be less or equal to 0."), ELogVerbosity::Warning);
		return;
	}

	Active = true;
	FTimerHandle ShuttingOffTimer;

	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(Timer, this, &UMiniTimer::_Update, TimerInterval, true);
	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(ShuttingOffTimer, this, &UMiniTimer::_Finish, TimerDuration);

}

void UMiniTimer::_Update()
{
	Update.Broadcast();
}

void UMiniTimer::_Finish()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(Timer);
	Timer.Invalidate();
	Finished.Broadcast();
	Active = false;
}





