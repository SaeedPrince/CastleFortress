// Fill out your copyright notice in the Description page of Project Settings.

#include "MovePawnToLocation.h"

UMovePawnToLocation* UMovePawnToLocation::MovePawnToLocation(const UObject* WorldContextObject, APawn* Pawn, FVector ActorLocation, const float AcceptableDistance, const float MoveInterval, const float EndTime)
{
	UMovePawnToLocation* Node = NewObject<UMovePawnToLocation>();
	Node->WorldContextObject = WorldContextObject;
	Node->Pawn = Pawn;
	Node->ActorLocation = ActorLocation;
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

	Okay = false;
	if (_IsPawnCloseToActor())
	{
		Okay = true;
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

bool UMovePawnToLocation::_IsPawnCloseToActor()
{
	bool retBool = false;
	FVector CharacterLocation = Pawn->GetActorLocation();
	FVector DistanceVector = ActorLocation - CharacterLocation;
	if (DistanceVector.Size() <= AcceptableDistance)
	{
		retBool = true;
	}
	return retBool;
}


void UMovePawnToLocation::_MoveControl()
{
	if (_IsPawnCloseToActor())
	{
		Okay = true;
		_Finish();
	}
	else
	{
		_MoveOnePoint();
	}
}

void UMovePawnToLocation::_MoveOnePoint()
{
	FVector CharacterLocation = Pawn->GetActorLocation();
	FVector DistanceVector = ActorLocation - CharacterLocation;
	Pawn->AddMovementInput(DistanceVector, 1.0f);
}

void UMovePawnToLocation::_Finish()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerMoveControl);
	TimerMoveControl.Invalidate();
	Finished.Broadcast(Okay);
	Active = false;
}