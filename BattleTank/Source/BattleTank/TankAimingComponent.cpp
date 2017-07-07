// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(const FVector HitLocation, const float LaunchSpeed) const
{
	if (!Barrel) { return; }	// Stop if barrel is not set
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));	// get socket "Projectile" in this component 
	bool foundVelocity = UGameplayStatics::SuggestProjectileVelocity
	(
		this, OutLaunchVelocity,
		StartLocation, HitLocation,
		LaunchSpeed, false,	0.0, 0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (foundVelocity)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		FString TankLoc = GetOwner()->GetActorLocation().ToString();
		FString TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("T%s LOC: %s Aiming Direction: %s"), *TankName, *TankLoc, *AimDirection.ToString());
	}
}



