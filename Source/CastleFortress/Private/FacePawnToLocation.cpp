// Fill out your copyright notice in the Description page of Project Settings.

#include "FacePawnToLocation.h"

UFacePawnToLocation* UFacePawnToLocation::FacePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector ActorLocation, const float AcceptableAngle, const float TurnInterval, const float EndTime)
{
	UFacePawnToLocation* Node = NewObject<UFacePawnToLocation>();
	Node->WorldContextObject = WorldContextObject;
	Node->Pawn = Pawn;
	Node->ActorLocation = ActorLocation;
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
		FFrame::KismetExecutionMessage(TEXT("MiniTimer is already running."), ELogVerbosity::Warning);
		return;
	}

	Okay = false;
	if (_IsPawnFacingToActor())
	{
		Okay = true;
	}
	else
	{
		FTimerHandle TimerEndTime;
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerTurnControl, this, &UFacePawnToLocation::_TurnControl, TurnInterval, true);
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerEndTime, this, &UFacePawnToLocation::_Finish, EndTime);
	}

}

bool UFacePawnToLocation::_IsPawnFacingToActor()
{
	bool retBool = false;
	return retBool;
}

float UFacePawnToLocation::_AngleBetweenVecs(FVector VectorA, FVector VectorB)
{
	float retFloat = 0;
	return retFloat;
}

void UFacePawnToLocation::_TurnControl()
{

}

void UFacePawnToLocation::_Finish()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerTurnControl);
	TimerTurnControl.Invalidate();
	Finished.Broadcast(Okay);
	Active = false;
}



