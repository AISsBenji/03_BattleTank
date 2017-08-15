// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Controller.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank"))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Possessed Tank : %s"), *ControlledTank->GetName())
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );	
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; // Out parameter
	if (GetSightRayHitLocation(OutHitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *OutHitLocation.ToString())
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{	
	return GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(1920, 1080, OutHitLocation, OutHitLocation);
}


