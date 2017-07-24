// Copyright @ 2017 C-Tech Studios

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// Get Tanks position
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	// Move Tank Forward if needed
	float ForwardThrow = TankForward | AIForwardIntention;	// Dot product 
	IntendMoveForward(ForwardThrow);
	// Turn Tank if needed
	float TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendMoveTurn(TurnThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; } // Stop if Track references are not set

	// Move Tracks up or down (depending on thumbstick)
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveTurn(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; } // Stop if Track references are not set

	// Move Tracks up or down (depending on thumbstick)
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
