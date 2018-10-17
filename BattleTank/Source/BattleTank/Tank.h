// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


// forward declaration
class UTankBarrel;
class ABullet;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;


private:
	const float ReloadTimeInSeconds = 3.0f;

	double LastFireTime = 0.0f;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; // TODO Remove


public:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ABullet> Bullet;

	// TODO remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;



public:
	UFUNCTION(BlueprintCallable)
	void Fire();
};
