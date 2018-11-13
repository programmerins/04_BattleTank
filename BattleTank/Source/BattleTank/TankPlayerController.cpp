// Copyright EmbraceIT Ltd.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
///#include "DrawDebugHelpers.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) { return;  }

	UTankAimingComponent* AimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimComponent)) { return; }

	FoundAimingComponent(AimComponent);
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }

	UTankAimingComponent* AimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimComponent)) { return; }

	FVector HitLocation = FVector::ZeroVector; /// Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(OUT HitLocation);

	if (GetSightRayHitLocation(OUT HitLocation)) /// Has "side-effect", is going to line trace
	{
		// TODO: Tell controlled tank to aim at this point
		AimComponent->AimAt(HitLocation);
	}	
}


// Get world location of line-trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	// TODO: 실제 에임 위젯의 위치를 가져와 정확하게 계산하기 (오버헤드 최적화 필요)
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, OUT LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, OUT HitLocation);
	}

	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; /// To be discarded

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, ScreenLocation.Y, 
		OUT CameraWorldLocation, OUT LookDirection
	);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult	HitResult;
	FVector		StartLocation	= PlayerCameraManager->GetCameraLocation();
	FVector		EndLocation		= StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(OUT HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}


void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);

		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	}
}


void ATankPlayerController::OnPossedTankDeath()
{
	StartSpectatingOnly();
}
