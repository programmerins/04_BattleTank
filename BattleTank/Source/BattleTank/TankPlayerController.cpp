// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

#include "DrawDebugHelpers.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* HasController = GetControlledTank();
	if (!HasController)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController no prossesing a tank."))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *HasController->GetName());
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank())
	{
		FVector HitLocation = FVector::ZeroVector; /// Out parameter

		if (GetSightRayHitLocation(OUT HitLocation)) /// Has "side-effect", is going to line trace
		{
			// TODO: Tell controlled tank to aim at this point
			GetControlledTank()->AimAt(HitLocation);
		}	
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
		if (GetLookVectorHitLocation(LookDirection, OUT HitLocation))
		{
			return true;
		}
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

	/// Test a draw debug line
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red);

	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult, 
		StartLocation, EndLocation, 
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}
