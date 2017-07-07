// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* tank = GetControllerTank();
	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("SUPER::BEGINPLAY --- %s"), *tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SUPER::BEGINPLAY --- NO POSSESSED TANK"));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshairs();
}

ATank* ATankPlayerController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshairs()
{
	if (!GetControllerTank()) { return; }

	FVector HitLocation;	// Out parameter
	
	// if it hits landscape
	if (GetSightRayHitLocation(HitLocation))	// "side-effect" Will Ray Trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

	}
		// tell controlled tank to aim at this point
}

// Get World Location if linetrace through crosshair, return true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" screen position of cross hair to world direction
	FVector LookDirection;		// holds look direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-Trace along LookDirection, and see what we hit (up to max range)
		//UE_LOG(LogTemp, Warning, TEXT("LOCATION: %s"), *LookDirection.ToString());
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// "De-project" screen position of cross hair to world direction
	FVector CameraLocation;	// temp variable needed for parameter
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		// Set Hit Location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;	// line traced failed
}
