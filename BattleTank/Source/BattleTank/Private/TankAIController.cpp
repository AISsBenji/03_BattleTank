// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledAITank = GetControlledAITank();
	if (!ControlledAITank) {
		UE_LOG(LogTemp, Error, TEXT("AIController not possessing a tank"))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Possessed AI Tank : %s"), *ControlledAITank->GetName())
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("AIController can't find the player tank"))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController find a Player Tank : %s"), *GetPlayerTank()->GetName())
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetControlledAITank()) { return; }

	if (GetPlayerTank()) {
		GetControlledAITank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAIController::GetControlledAITank() const {
	return Cast<ATank>(GetPawn());
}
