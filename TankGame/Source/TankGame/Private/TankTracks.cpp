#include "TankTracks.h"


void UTankTracks::SetTrackThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TankMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
