#include "TankMovementComponent.h"
#include "TankTracks.h"



void UTankMovementComponent::Initialize(UTankTracks* RightTrackToSet, UTankTracks* LeftTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}



void UTankMovementComponent::MoveForward(float Throttle)
{
	RightTrack->SetTrackThrottle(Throttle);
	LeftTrack->SetTrackThrottle(Throttle);
}



void UTankMovementComponent::MoveBackward(float Throttle)
{
	RightTrack->SetTrackThrottle(-Throttle);
	LeftTrack->SetTrackThrottle(-Throttle);
}



void UTankMovementComponent::MoveRight(float Throttle)
{
	RightTrack->SetTrackThrottle(Throttle);
	LeftTrack->SetTrackThrottle(-Throttle);
}



void UTankMovementComponent::MoveLeft(float Throttle)
{
	RightTrack->SetTrackThrottle(-Throttle);
	LeftTrack->SetTrackThrottle(Throttle);
}