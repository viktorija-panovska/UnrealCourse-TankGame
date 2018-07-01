#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller is not possesing anything"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Controller is possessing: %s"), *(ControlledTank->GetName()));
	}

}



void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



// Move the tank barrel to aim at the crosshair on the UI
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {	return;	}
	

	// Find the hit location
	FVector HitLocation;  //OUT parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}



// Return true if the crosshair is aiming at the terrain
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find crosshair position in pixels
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D((ViewportSizeX*CrosshairLocationX), (ViewportSizeY*CrosshairLocationY));


	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace to see if we hit the terrain
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}



// De-projecting the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation; //temporary

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}



// Line-tracing through the crosshair
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0);
	return false;
}