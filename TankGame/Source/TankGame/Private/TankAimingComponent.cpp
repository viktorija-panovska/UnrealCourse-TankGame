#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



// Aims at the location provided by the tank
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto TankName = GetOwner()->GetName();

	if (!Barrel) {return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("%f:  Tank %s No solution has been found"), Time, *TankName);
	}
}



// Setter function for the barrel
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}



// Setter function for the turret
void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}



// Moves the barrel to the desired location
void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Barrel elevation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaAimRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaAimRotator.Pitch);

	Turret->Rotate(DeltaAimRotator.Yaw);
}