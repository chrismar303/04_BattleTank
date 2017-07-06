// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"


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
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());

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
	// Line-Trace along look direction, and see what we hit (up to max range)


	OutHitLocation = FVector(1.0f);
	return true;
}