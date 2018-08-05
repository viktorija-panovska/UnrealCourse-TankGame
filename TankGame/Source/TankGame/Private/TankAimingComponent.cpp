#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



// Called when the game starts or player is spawned
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}



// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}



void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



// Aims at the location provided by the tank
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) {return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}



// Moves the barrel to the desired location
void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	// Barrel elevation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaAimRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaAimRotator.Pitch);

	if (FMath::Abs(DeltaAimRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaAimRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaAimRotator.Yaw);
	}
}



// Returns true if barrel is moving
bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01);
}



// Fires projectile
void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		
		// Spawn projectile at the end of the barrel socket
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("ProjectileSocket")), Barrel->GetSocketRotation(FName("ProjectileSocket")));
		Projectile->LaunchProjectile(LaunchSpeed);	

		LastFireTime = FPlatformTime::Seconds();

		if (RoundsLeft > 0)
		{
			RoundsLeft--;
		}
	}
}



EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}