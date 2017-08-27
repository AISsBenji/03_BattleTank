// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	auto LeftTrackForceApplied = LeftTrack->GetForwardVector() * Throw * MaxForce;
	LeftTrack->AddForceAtLocation(LeftTrackForceApplied, LeftTrack->GetComponentLocation());

	auto RightTrackForceApplied = RightTrack->GetForwardVector() * Throw * MaxForce;
	RightTrack->AddForceAtLocation(RightTrackForceApplied, RightTrack->GetComponentLocation());
}


