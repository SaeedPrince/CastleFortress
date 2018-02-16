// Fill out your copyright notice in the Description page of Project Settings.

#include "MovePawnToLocation.h"

UMovePawnToLocation* UMovePawnToLocation::MovePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector Destination, const float AcceptableDistance, const float MoveInterval, const float EndTime)
{
	UMovePawnToLocation* Node = NewObject<UMovePawnToLocation>();
	Node->WorldContextObject = WorldContextObject;
	Node->Pawn = Pawn;
	Node->Destination = Destination;
	Node->AcceptableDistance = AcceptableDistance;
	Node->MoveInterval = MoveInterval;
	Node->EndTime = EndTime;
	return Node;

}

void UMovePawnToLocation::Activate()
{
	if (nullptr == WorldContextObject)
	{
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject."), ELogVerbosity::Error);
		return;
	}
	if (Active)
	{
		FFrame::KismetExecutionMessage(TEXT("Is already running."), ELogVerbosity::Warning);
		return;
	}

	placeOkay = false;
	if (_IsPawnCloseToActor())
	{
		placeOkay = true;
		_Finish();
	}
	else
	{
		FTimerHandle TimerEndTime;
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerMoveControl, this, &UMovePawnToLocation::_MoveControl, MoveInterval, true);
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerEndTime, this, &UMovePawnToLocation::_Finish, EndTime);
	}
	Active = true;
}

void UMovePawnToLocation::_MoveControl()
{
	if (_IsPawnCloseToActor())
	{
		placeOkay = true;
		_Finish();
	}
	else
	{
		_MoveOnePoint();
	}
}

void UMovePawnToLocation::_Finish()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerMoveControl);
	TimerMoveControl.Invalidate();
	Finished.Broadcast(placeOkay);
	Active = false;
}