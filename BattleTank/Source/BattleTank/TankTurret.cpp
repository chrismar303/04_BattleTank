// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; 
	float Rotation = RelativeRotation.Yaw + RotationChange;		// compute change
	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
	UE_LOG(LogTemp, Warning, TEXT("Rotation Change: %f"), Rotation);
}
