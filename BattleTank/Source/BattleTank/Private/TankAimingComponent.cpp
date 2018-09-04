// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this rellay tick?

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (Barrel)
	{
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OUT OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

		if (bHaveAimSolution) /// Calculate the OutLaunchVelocity
		{
			FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
		}

		// If no solution found do nothing
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation, and AimDirection
	FRotator BarrelRotator	= Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator	= AimDirection.Rotation();
	FRotator DeltaRotator	= AimAsRotator - BarrelRotator;

	Barrel->Elevate(5.0f); // TODO: remove magic number
}
