// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Check if Player Tank exist, Stop if it doesnt
	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank) { return; }
	
	// Grab AI Tank
	ATank* ControlledTank = GetControlledTank();
	// TODO Move Towards Player

	// Aim Towards Player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	// Fire
	ControlledTank->Fire();		// TODO limit firing rate
} 

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


