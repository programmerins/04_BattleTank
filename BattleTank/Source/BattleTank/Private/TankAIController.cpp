// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* TargetTank		= Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank	= Cast<ATank>(GetPawn());

	if (TargetTank && ControlledTank)
	{
		// TODO Move towards the player

		// Aim at the player
		ControlledTank->AimAt(TargetTank->GetActorLocation());

		ControlledTank->Fire(); // TODO: don't fire every frame
	}
}
