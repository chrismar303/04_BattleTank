// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(const FVector HitLocation, const float LaunchSpeed)
{
	if (!Barrel) { return; }	// Stop if barrel is not set
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));	// get socket "Projectile" in this component 
	bool bFoundVelocity = UGameplayStatics::SuggestProjectileVelocity
	(
		this, OutLaunchVelocity,
		StartLocation, HitLocation, LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bFoundVelocity)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("T%s LOC: %s Aiming Direction: %s"), *TankName, *TankLoc, *AimDirection.ToString());
	}
	// Do nothing if not found
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	// Workout difference between current barrel rotation vs desired barrel rotation
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	
	Barrel->Elevate(5);		//TODO REMOVE MAGIC NUMBER
}



