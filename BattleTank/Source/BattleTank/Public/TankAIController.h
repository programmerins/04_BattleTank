// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void Tick(float DeltaTime) override;

private:
	// How close can the AI tank get
	const float AcceptanceRadius = 3000.0f;
};
