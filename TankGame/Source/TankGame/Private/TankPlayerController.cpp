#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"



// Called when the game starts or player is spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) { return; }

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);
	
}



// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}



void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}



void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}


// Move the tank barrel to aim at the crosshair on the UI
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	// Find the hit location
	FVector HitLocation;  //OUT parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
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
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}



// De-projecting the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation;

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