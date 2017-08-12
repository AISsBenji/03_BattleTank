// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Controller.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledAITank = GetControlledAITank();
	if (!ControlledAITank) {
		UE_LOG(LogTemp, Error, TEXT("AIController not possessing a tank"))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Possessed AI Tank : %s"), *ControlledAITank->GetName())
	}
}

ATank* ATankAIController::GetControlledAITank() const {
	return Cast<ATank>(GetPawn());
}