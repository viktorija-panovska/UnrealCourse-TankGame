#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"



UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};



UCLASS( meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Setter function for the barrel and turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(class UTankBarrel* BarrelToSet, class UTankTurret* TurretToSet);

	// Aims at the location provided by the tank
	void AimAt(FVector HitLocation, float LaunchSpeed);

	// Setter function for the barrel
	void SetBarrelReference(class UTankBarrel* BarrelToSet);

	// Setter function for the turret
	void SetTurretReference(class UTankTurret* TurretToSet);

	// Moves the barrel to the desired location
	void MoveBarrel(FVector AimDirection);


protected:
	UPROPERTY(BlueprintReadOnly, Category = "FiringState")
	EFiringState InitialFiringState = EFiringState::Reloading;


private:
	class UTankBarrel* Barrel = nullptr;

	class UTankTurret* Turret = nullptr;
};
