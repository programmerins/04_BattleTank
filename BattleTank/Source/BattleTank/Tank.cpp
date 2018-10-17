// Copyright EmbraceIT Ltd.

#include "Tank.h"
#include "TankBarrel.h"
#include "Bullet.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }

	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (IsReloaded)
	{
		// Spawn a bullet at the socket location on the barrel
		ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>
		(
			Bullet, 
			Barrel->GetSocketLocation(FName("Muzzle")), 
			Barrel->GetSocketRotation(FName("Muzzle"))
		);

		NewBullet->LaunchBullet(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
