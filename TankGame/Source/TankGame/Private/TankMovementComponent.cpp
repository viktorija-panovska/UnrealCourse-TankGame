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



void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrottle = FVector::DotProduct(TankForward, AIForwardIntention);
	MoveForward(ForwardThrottle);

	auto TurnThrottle = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	MoveRight(TurnThrottle);
}