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
	auto AimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimComponent->AimAt(TargetTank->GetActorLocation());

	// TODO: don't fire every frame
	// TODO fix firing
	// ControlledTank->Fire();
}
