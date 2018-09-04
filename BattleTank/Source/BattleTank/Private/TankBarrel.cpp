// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	float DeltaTime = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Log, TEXT("%f - called UTankBarrel::Elevate(%f)"), DeltaTime, RelativeSpeed)
}
