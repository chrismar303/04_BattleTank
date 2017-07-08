// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RotationChange + RelativeRotation.Yaw;
	float Rotation = FMath::Clamp<float>(RawNewRotation, MinRotationDegrees, MaxRotationDegrees);

	SetRelativeRotation(FRotator(0.0f, RawNewRotation, 0.0f));
	UE_LOG(LogTemp, Warning, TEXT("Rotation Change: %f"), Rotation);
}
