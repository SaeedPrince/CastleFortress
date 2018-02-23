// Fill out your copyright notice in the Description page of Project Settings.

#include "CaladanLibrary.h"

FString UCaladanLibrary::HitJoint(const FString PrimitiveComponentName)
{
	FString retString;

	return retString;
}


float UCaladanLibrary::IntPowerOfFloat(const float fltNumber, const int intNumber)
{
	float retFloat = 1.0f;
	for (int i = 0; i < intNumber; i++)
	{
		retFloat *= fltNumber;
	}
	return retFloat;
}

bool UCaladanLibrary::IsPointCloseToLocation(FVector Point, FVector Location, const float AcceptableDistance)
{
	bool retBool = false;
	FVector DistanceVec = Location - Point;
	float Distance = DistanceVec.Size();
	if (Distance <= AcceptableDistance)
	{
		retBool = true;
	}
	return retBool;
}

FVector UCaladanLibrary::HowPointCloseToLocation(FVector Point, FVector Location)
{
	FVector retVec;
	retVec = Location - Point;
	return retVec;
}
