// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//Tick
	PrimaryComponentTick.bCanEverTick = true;

	// InitializeComponent
	bWantsInitializeComponent = true;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringStates = EFiringStates::Reloading;
	} else if (IsBarrelMoving()) {
		FiringStates = EFiringStates::Aiming;
	} else {
		FiringStates = EFiringStates::Locked;
	}
}

EFiringStates UTankAimingComponent::GetFiringState() const
{
	return FiringStates;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto ForwardVector = Barrel->GetForwardVector();
	return !ForwardVector.Equals(AimDirection, 0.01);
}


void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) { return; } 

	// Calculate the OutLaunchVelocity
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!ensure(Barrel || !Turret)) { return; }

	// Work-out difference between current barrel direction, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = BarrelRotator - AimAsRotator;

	Barrel->Elevate(-DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(Barrel || !Turret)) { return; }

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = TurretRotator - AimAsRotator;

	if (DeltaRotator.Yaw < 180.f && DeltaRotator.Yaw > -180.f) {
		Turret->Rotate(-DeltaRotator.Yaw);
	} else {
		Turret->Rotate(DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire() {
	if (FiringStates != EFiringStates::Reloading) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}




