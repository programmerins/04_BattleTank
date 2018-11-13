// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()


public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	

public:
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 50000000.0f; /// Assume 40 tonne tank, and 1g accelleration


private:
	UTankTrack();

	virtual void BeginPlay() override;

	TArray<class ASprungWheel*> GetWheels() const;

	void DriveTrack(float CurrentThrottle);
};
