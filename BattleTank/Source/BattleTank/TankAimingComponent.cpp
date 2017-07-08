// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"

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

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(const FVector HitLocation, const float LaunchSpeed)
{
	if (!Barrel || !Turret) { return; }	// Stop if barrel is not set
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));	// get socket "Projectile" in this component 
	bool bFoundVelocity = UGameplayStatics::SuggestProjectileVelocity
	(
		this, OutLaunchVelocity,
		StartLocation, HitLocation, LaunchSpeed,
		false, 0.0f, 0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bFoundVelocity)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);	// move up or down
		MoveTurretToward(AimDirection);	// move left or right
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No AIM SOLUTION FOUND"), Time);
	}
	// Do nothing if not found
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	// Workout difference between current barrel rotation vs desired barrel rotation
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	
	Barrel->Elevate(DeltaRotator.Pitch);		
}


void UTankAimingComponent::MoveTurretToward(FVector AimDirection)
{
	FRotator TurretRotation = Turret->GetRightVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotation;
	
	if (FMath::Abs<float>(DeltaRotator.Yaw))
	{
		Turret->Rotate(DeltaRotator.Yaw);	
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}