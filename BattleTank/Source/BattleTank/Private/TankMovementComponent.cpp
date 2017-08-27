// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }

	auto LeftTrackForceApplied = LeftTrack->GetForwardVector() * Throw * MaxForce;
	LeftTrack->AddForceAtLocation(LeftTrackForceApplied, LeftTrack->GetComponentLocation());

	auto RightTrackForceApplied = RightTrack->GetForwardVector() * Throw * MaxForce;
	RightTrack->AddForceAtLocation(RightTrackForceApplied, RightTrack->GetComponentLocation());
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }

	auto LeftTrackForceApplied = LeftTrack->GetForwardVector() * Throw * MaxForce;
	LeftTrack->AddForceAtLocation(LeftTrackForceApplied, LeftTrack->GetComponentLocation());

	auto RightTrackForceApplied = RightTrack->GetForwardVector() * -Throw * MaxForce;
	RightTrack->AddForceAtLocation(RightTrackForceApplied, RightTrack->GetComponentLocation());
}

