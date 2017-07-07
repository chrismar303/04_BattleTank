// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (Tank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AI CONTROLLER FOUND PLAYER CONTROLLER: %s"), *Tank->GetName()); 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI CONTROLLER DID NOT FIND PLAYER CONTROLLER")); 
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Check if Player Tank exist, Stop if it doesnt
	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank)
		return;
	
	// TODO Move Towards Player

	// Aim Towards Player
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	// Fire
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


