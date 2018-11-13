// Copyright EmbraceIT Ltd.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
// Depends on movement component via pathfinding system


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* TargetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledTank = GetPawn();

	if (!(TargetTank && ControlledTank)) { return; }

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


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}


void ATankAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())) { return; } // TODO remove if ok

	GetPawn()->DetachFromControllerPendingDestroy();
}
