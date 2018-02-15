// Fill out your copyright notice in the Description page of Project Settings.

#include "AsyncAction.h"

UAsyncAction* UAsyncAction::AsyncAction(const UObject* WorldContextObject, const float UpdateInterval, const float EndTime)
{
	UAsyncAction* Node = NewObject<UAsyncAction>();
	Node->WorldContextObject = WorldContextObject;
	Node->UpdateInterval = UpdateInterval;
	Node->EndTime = EndTime;
	return Node;
}

void UAsyncAction::Activate()
{
	if (nullptr == WorldContextObject)
	{
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject."), ELogVerbosity::Error);
		return;
	}
	if (Active)
	{
		FFrame::KismetExecutionMessage(TEXT("Already running."), ELogVerbosity::Warning);
		return;
	}
	Active = true;
	_Start();
	FTimerHandle ShuttingOffTimer;
	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerUpdate, this, &UAsyncAction::_Update, UpdateInterval, true);
	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(ShuttingOffTimer, this, &UAsyncAction::_Finish, EndTime);
}

void UAsyncAction::_Start()
{
	Start.Broadcast();
}

void UAsyncAction::_Update()
{
	Update.Broadcast();
}

void UAsyncAction::_Finish()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerUpdate);
	TimerUpdate.Invalidate();
	Finish.Broadcast();
	Active = false;
}
