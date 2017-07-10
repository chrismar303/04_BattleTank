// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"	
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
private:
	ATank* GetControlledTank() const;

	// Start Tank Moving Barrel
	void AimAtCrosshairs();
	// Return an OUT parameter -- Return true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.50f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333f;

	// Returns OUT PARAMETER
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;	// 10km

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
