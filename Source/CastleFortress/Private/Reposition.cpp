// Fill out your copyright notice in the Description page of Project Settings.

#include "Reposition.h"

UReposition* UReposition::Reposition(const UObject* WorldContextObject, APawn* Pawn, FVector ActorLocation, const float AcceptableAngle, const float AcceptableDistance, const float TurnInterval, const float MoveInterval, const float EndTime)
{
	UReposition* Node = NewObject<UReposition>();
	Node->WorldContextObject = WorldContextObject;
	Node->Pawn = Pawn;
	Node->ActorLocation = ActorLocation;
	Node->AcceptableAngle = AcceptableAngle;
	Node->AcceptableDistance = AcceptableDistance;
	Node->TurnInterval = TurnInterval;
	Node->MoveInterval = MoveInterval;
	Node->EndTime = EndTime;
	return Node;

}

void UReposition::Activate()
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
	if (_IsPawnFacingToActor()&&_IsPawnCloseToActor())
	{
		Okay = true;
		_Finish();
	}
	else
	{
		FTimerHandle TimerEndTime;
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerTurnControl, this, &UReposition::_TurnControl, TurnInterval, true);
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerMoveControl, this, &UReposition::_MoveControl, MoveInterval, true);
		float DoneInterval;
		if (MoveInterval > TurnInterval)
		{
			DoneInterval = MoveInterval;
		}
		else
		{
			DoneInterval = TurnInterval;
		}
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerDoneControl, this, &UReposition::_DoneControl, DoneInterval, true);
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerEndTime, this, &UReposition::_Finish, EndTime);
	}
	Active = true;
}

bool UReposition::_IsPawnFacingToActor()
{
	bool retBool = false;
	FVector CharacterLocation = Pawn->GetActorLocation();
	FVector DistanceVector = ActorLocation - CharacterLocation;
	FVector DirectionVector = _PawnDirection();
	float anyFloat = _AngleBetweenVecs(DistanceVector, DirectionVector);
	if (anyFloat <= AcceptableAngle)
	{
		retBool = true;
	}
	return retBool;
}

bool UReposition::_IsPawnCloseToActor()
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


FVector UReposition::_PawnDirection()
{
	FRotator MyRot = Pawn->GetActorRotation();
	FVector RotXVector = MyRot.Vector();
	return RotXVector;
}

float UReposition::_AngleBetweenVecs(FVector DistanceVector, FVector DirectionVector)
{
	float retFloat = 0;
	FVector a = FVector(DistanceVector.X, DistanceVector.Y, 0);
	a.Normalize();
	FVector b = FVector(DirectionVector.X, DirectionVector.Y, 0);
	b.Normalize();
	float dtproduct = FVector::DotProduct(a, b);
	float radValue = FGenericPlatformMath::Acos(dtproduct);
	retFloat = FMath::RadiansToDegrees(radValue);
	return retFloat;
}

float UReposition::_ClockWise()
{
	float retFloat;
	FVector CharacterLocation = Pawn->GetActorLocation();
	FVector DistanceVector = ActorLocation - CharacterLocation;
	FVector DirectionVector = _PawnDirection();
	FVector crssproduct = FVector::CrossProduct(DistanceVector, DirectionVector);
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

void UReposition::_TurnControl()
{
	if (_IsPawnFacingToActor())
	{
		faceOkay = true;
	}
	else
	{
		_TurnOnePoint(_ClockWise());
	}
}

void UReposition::_MoveControl()
{
	if (_IsPawnCloseToActor())
	{
		placeOkay = true;
	}
	else
	{
		_MoveOnePoint();
	}
}

void UReposition::_DoneControl()
{
	if (faceOkay && placeOkay)
	{
		Okay = true;
		_Finish();
	}
}


void UReposition::_TurnOnePoint(float Value)
{
	FRotator finalRot = Pawn->GetActorRotation();
	finalRot.Yaw += Value;
	Pawn->SetActorRotation(finalRot);
}

void UReposition::_MoveOnePoint()
{
	FVector CharacterLocation = Pawn->GetActorLocation();
	FVector DistanceVector = ActorLocation - CharacterLocation;
	Pawn->AddMovementInput(DistanceVector, 1.0f);
}

void UReposition::_Finish()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerTurnControl);
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerMoveControl);
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerDoneControl);
	TimerTurnControl.Invalidate();
	TimerMoveControl.Invalidate();
	TimerDoneControl.Invalidate();
	Finished.Broadcast(Okay);
	Active = false;
}