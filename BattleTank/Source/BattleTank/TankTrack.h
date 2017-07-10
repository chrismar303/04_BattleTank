// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	// Sets a Throttle between -1 or +1
	UFUNCTION(BlueprintCallable, Category = Inputs)
	void SetThrottle(float Throttle);
	
	// Max Force Per Track, in Newtons ( kg * acceleration )
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float TrackMaxDrivingForce = 400000.0f;		// 40 Ton Tank and 1g Acceleration


};
