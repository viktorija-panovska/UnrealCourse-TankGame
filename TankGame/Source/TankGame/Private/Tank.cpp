#include "Tank.h"
#include "TankBarrel.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"



// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}



// Called when the game starts or player is spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}



// Aims at the location provided by the tank controller
void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}



// Fires projectile
void ATank::Fire()
{
	// TODO make tank fire only when aiming at player

	if (!ensure(Barrel)) {	return;	}

	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (bIsReloaded)
	{
		// Spawn projectile at the end of the barrel socket
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("ProjectileSocket")), Barrel->GetSocketRotation(FName("ProjectileSocket")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}