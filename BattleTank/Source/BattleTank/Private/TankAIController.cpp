// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank = Cast<ATank>(GetPawn());

	if (!AITank) { return; }

	if (PlayerTank) {
		// TODO Move towards the player

		// Aim towards the player
		AITank->AimAt(PlayerTank->GetActorLocation());

		AITank->Fire(); // TODO limit firing rate
	}
}

