// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	void AimTowardsCrosshair();

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5F;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333F;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.F;
};
