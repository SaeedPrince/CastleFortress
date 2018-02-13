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

bool UFacePawnToLocation::_IsPawnFacingToActor()
{
	bool retBool = false;
	FVector CharacterLocation = Pawn->GetActorLocation();
	FVector VectorA = ActorLocation - CharacterLocation;
	FVector VectorB = _PawnDirection();
	float anyFloat;
	anyFloat = _AngleBetweenVecs(VectorA, VectorB);
	if (anyFloat <= AcceptableAngle)
	{
		retBool = true;
	}
	return retBool;
}

FVector UFacePawnToLocation::_PawnDirection()
{
	FRotator MyRot = Pawn->GetActorRotation();
	FVector RotXVector = MyRot.Vector();
	return RotXVector;
}

float UFacePawnToLocation::_AngleBetweenVecs(FVector VectorA, FVector VectorB)
{
	float retFloat = 0;
	FVector a = FVector(VectorA.X, VectorA.Y, 0);
	a.Normalize();
	FVector b = FVector(VectorB.X, VectorB.Y, 0);
	b.Normalize();
	float dtproduct = FVector::DotProduct(a, b);
	float radValue = FGenericPlatformMath::Acos(dtproduct);
	retFloat = FMath::RadiansToDegrees(radValue);
	return retFloat;
}

float UFacePawnToLocation::_ClockWise()
{
	float retFloat;
	FVector CharacterLocation = Pawn->GetActorLocation();
	FVector VectorA = ActorLocation - CharacterLocation;
	FVector VectorB = _PawnDirection();
	FVector crssproduct = FVector::CrossProduct(VectorA, VectorB);
	if (crssproduct.Z > 0)
	{
		retFloat = -1;
	}
	else
	{
		retFloat = 1;

	}
	return retFloat;
}

void UFacePawnToLocation::_TurnControl()
{
	if (_IsPawnFacingToActor())
	{
		Okay = true;
		_Finish();
	}
	else
	{
		_TurnOnePoint(_ClockWise());
	}
}

void UFacePawnToLocation::_TurnOnePoint(float Value)
{
	FRotator finalRot =	Pawn->GetActorRotation();
	finalRot.Yaw += Value;
	Pawn->SetActorRotation(finalRot);
}

void UFacePawnToLocation::_Finish()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerTurnControl);
	TimerTurnControl.Invalidate();
	Finished.Broadcast(Okay);
	Active = false;
}



