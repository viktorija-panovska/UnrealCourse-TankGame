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



void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {	return;	}
	

	FVector HitLocation;  //OUT parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation is: %s"), *(HitLocation.ToString()));
	}
}



bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find crosshair positing in pixels
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D((ViewportSizeX*CrosshairLocationX), (ViewportSizeY*CrosshairLocationY));


	//De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("LookDirection is: %s"), *(LookDirection.ToString()));
	}


	return true;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation; //temporary

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}