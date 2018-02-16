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


