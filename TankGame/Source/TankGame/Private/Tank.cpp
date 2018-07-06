#include "Tank.h"
#include "TankBarrel.h"
#include "Tank.h"
#include "TankAimingComponent.h"



// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the aiming component
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



// Sets up the barrel
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}



// Sets up the turret
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}



// Aims at the location provided by the tank controller
void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}