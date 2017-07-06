// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetPlayerTank();
	if (Tank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AI CONTROLLER FOUND PLAYER CONTROLLER: %s"), *Tank->GetName()); 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI CONTROLLER DID NOT FIND PLAYER CONTROLLER")); 
	}
}

ATank* ATankAIController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}




