// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// forward declarations
class UTankBarrel;

// Hold barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:
	void AimAt(FVector HitLocation, float LaunchSpeed);

	FORCEINLINE void SetTurretReference(UStaticMeshComponent* TurretToSet) { Turret = TurretToSet; }

	FORCEINLINE void SetBarrelReference(UTankBarrel* BarrelToSet) { Barrel = BarrelToSet; }

private:
	UStaticMeshComponent* Turret = nullptr;

	UTankBarrel* Barrel = nullptr;

private:
	void MoveBarrelTowards(FVector AimDirection);
};