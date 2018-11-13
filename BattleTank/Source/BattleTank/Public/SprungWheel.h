// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPhysicsConstraintComponent* PhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPhysicsConstraintComponent* AxleConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0.f;

private:
	void SetupConstraint();

	void ApplyForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
