// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank = GetPawn();

	if (!ensure(PlayerTank) && !ensure(AITank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// if aim or locked 
	if (AimingComponent->GetFiringState() == EFiringStates::Locked) {
		AimingComponent->Fire();
	}	
}

