// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed			= FMath::Clamp<float>(RelativeSpeed, -1, 1);

	float RotationChange	= RelativeSpeed * (MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds);
	float Rotation			= RelativeRotation.Yaw + RotationChange;

	// TODO 터렛 회전에 보간 먹이기
	SetRelativeRotation(
		FRotator(0, Rotation, 0)
	);
}
