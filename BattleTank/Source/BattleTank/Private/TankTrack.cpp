// Copyright EmbraceIT Ltd.
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	// TOOD clamp actual throttle value so player can't over-drive
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
