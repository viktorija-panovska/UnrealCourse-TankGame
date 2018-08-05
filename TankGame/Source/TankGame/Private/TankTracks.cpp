#include "TankTracks.h"



UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void UTankTracks::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}



void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	DriveTracks();
	ApplySidewaysForce(DeltaTime);
	CurrentThrottle = 0;
}



void UTankTracks::DriveTracks()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TankMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



void UTankTracks::ApplySidewaysForce(float DeltaTime)
{
	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -(SlipSpeed / DeltaTime * GetRightVector());

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;

	TankRoot->AddForce(CorrectionForce);
}



void UTankTracks::SetTrackThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}