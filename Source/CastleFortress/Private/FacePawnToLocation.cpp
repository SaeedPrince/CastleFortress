// Fill out your copyright notice in the Description page of Project Settings.

#include "FacePawnToLocation.h"

UFacePawnToLocation* UFacePawnToLocation::FacePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector Destination, const float AcceptableAngle, const float TurnInterval, const float EndTime)
{
	UFacePawnToLocation* Node = NewObject<UFacePawnToLocation>();
	Node->WorldContextObject = WorldContextObject;
	Node->Pawn = Pawn;
	Node->Destination = Destination;
	Node->AcceptableAngle = AcceptableAngle;
	Node->TurnInterval = TurnInterval;
	Node->EndTime = EndTime;
	return Node;

}

void UFacePawnToLocation::Activate()
{
	if (nullptr == WorldContextObject)
	{
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject. Cannot execute MiniTimer."), ELogVerbosity::Error);
		return;
	}
	if (Active)
	{
		FFrame::KismetExecutionMessage(TEXT("Is already running."), ELogVerbosity::Warning);
		return;
	}

	faceOkay = false;
	if (_IsPawnFacingToActor())
	{
		faceOkay = true;
		_Finish();
	}
	else
	{
		FTimerHandle TimerEndTime;
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerTurnControl, this, &UFacePawnToLocation::_TurnControl, TurnInterval, true);
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerEndTime, this, &UFacePawnToLocation::_Finish, EndTime);
	}
	Active = true;
}

void UFacePawnToLocation::_TurnControl()
{
	if (_IsPawnFacingToActor())
	{
		faceOkay = true;
		_Finish();
	}
	else
	{
		_TurnOnePoint(_ClockWise());
	}
}

void UFacePawnToLocation::_Finish()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerTurnControl);
	TimerTurnControl.Invalidate();
	Finished.Broadcast(faceOkay);
	Active = false;
}



