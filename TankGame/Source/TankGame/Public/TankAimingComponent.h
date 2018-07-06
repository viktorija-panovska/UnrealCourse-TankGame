#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"



UCLASS( meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();


public:
	// Aims at the location provided by the tank
	void AimAt(FVector HitLocation, float LaunchSpeed);

	// Setter function for the barrel
	void SetBarrelReference(class UTankBarrel* BarrelToSet);

	// Setter function for the turret
	void SetTurretReference(class UTankTurret* TurretToSet);

	// Moves the barrel to the desired location
	void MoveBarrel(FVector AimDirection);


private:
	class UTankBarrel* Barrel = nullptr;

	class UTankTurret* Turret = nullptr;
};
