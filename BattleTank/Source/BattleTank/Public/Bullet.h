// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"


// forward declaration
class UProjectileMovementComponent;


UCLASS()
class BATTLETANK_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchBullet(float Speed);

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;
};
