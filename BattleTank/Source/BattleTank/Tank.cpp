// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "UObject/UObjectGlobals.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(const FVector HitLocation) 
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() const
{
	UE_LOG(LogTemp, Warning, TEXT("%s is Firing!"), *GetName());
	if (!Barrel) { return; }	// if barrel has not been set, stop!

	// Spawn a projectile at Socket location
	FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

