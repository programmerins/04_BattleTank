// Copyright EmbraceIT Ltd.
#include "TankTrack.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}


TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;

	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }
	
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) { continue; }

		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}


void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}


void UTankTrack::DriveTrack(float CurrentThrottle)
{
	// TOOD clamp actual throttle value so player can't over-drive
	auto Wheels = GetWheels();
	float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	float ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}
