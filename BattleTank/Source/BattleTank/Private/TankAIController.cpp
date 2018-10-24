// Copyright EmbraceIT Ltd.

#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding system


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* TargetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledTank = GetPawn();

	if (!ensure(TargetTank && ControlledTank)) { return; }

	// TODO Move towards the player
	MoveToActor(TargetTank, AcceptanceRadius); // TODO check radius is in cm

	// Aim at the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(TargetTank->GetActorLocation());

	// if aiming or locked 
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}
