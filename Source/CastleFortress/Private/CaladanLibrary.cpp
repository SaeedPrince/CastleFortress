// Fill out your copyright notice in the Description page of Project Settings.

#include "CaladanLibrary.h"

float UCaladanLibrary::IntPowerOfFloat(const float fltNumber, const int intNumber)
{
	float retFloat = 1.0f;
	for (int i = 0; i < intNumber; i++)
	{
		retFloat *= fltNumber;
	}
	return retFloat;
}

bool UCaladanLibrary::IsPointCloseToLocation2D(FVector2D Point, FVector2D Location, const float AcceptableDistance)
{
	bool retBool = false;
	FVector2D DistanceVec = Location - Point;
	float Distance = DistanceVec.Size();
	if (Distance <= AcceptableDistance)
	{
		retBool = true;
	}
	return retBool;
}

FVector2D UCaladanLibrary::HowPointCloseToLocation2D(FVector2D Point, FVector2D Location)
{
	FVector2D retVec;
	retVec = Location - Point;
	return retVec;
}
