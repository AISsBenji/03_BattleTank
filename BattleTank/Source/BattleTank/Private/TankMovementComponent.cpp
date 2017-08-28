// Copyright Benjamin.K

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendMoveForward(ForwardThrow);

	IntendTurnRight(TurnThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (ensure(!LeftTrack && !RightTrack)) { return; }

	auto LeftTrackForceApplied = LeftTrack->GetForwardVector() * Throw * MaxForce;
	LeftTrack->AddForceAtLocation(LeftTrackForceApplied, LeftTrack->GetComponentLocation());

	auto RightTrackForceApplied = RightTrack->GetForwardVector() * Throw * MaxForce;
	RightTrack->AddForceAtLocation(RightTrackForceApplied, RightTrack->GetComponentLocation());
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (ensure(!LeftTrack && !RightTrack)) { return; }

	auto LeftTrackForceApplied = LeftTrack->GetForwardVector() * Throw * MaxForce;
	LeftTrack->AddForceAtLocation(LeftTrackForceApplied, LeftTrack->GetComponentLocation());

	auto RightTrackForceApplied = RightTrack->GetForwardVector() * -Throw * MaxForce;
	RightTrack->AddForceAtLocation(RightTrackForceApplied, RightTrack->GetComponentLocation());
}


