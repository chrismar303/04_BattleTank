// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move barrel right amount this frame
	// Given Max elevation amount, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);	// restrict speed of turret
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ElevationClamped = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(ElevationClamped, 0.0f, 0.0f));
}

