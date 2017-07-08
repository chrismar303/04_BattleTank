// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// FORWARD DECLARATION
class UTankBarrel;	
class UTankTurret;

// Holds Barrel's Properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	// Prepares Turret to be used
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation, const float LaunchSpeed);
	void MoveBarrelToward(const FVector AimDirection);
	void MoveTurretToward(const FVector AimDirection);

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
