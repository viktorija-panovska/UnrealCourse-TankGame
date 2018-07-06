#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;  // We need DeltaTimeSeconds to convert seconds to frames
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}