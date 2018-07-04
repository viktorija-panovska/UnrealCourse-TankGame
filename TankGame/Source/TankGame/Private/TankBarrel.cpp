#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;  // We need DeltaTimeSeconds to convert seconds to frames
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}