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


ATank* ATankPlayerController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}


