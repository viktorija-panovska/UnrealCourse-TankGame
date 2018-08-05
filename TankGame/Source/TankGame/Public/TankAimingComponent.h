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
	Locked,
	OutOfAmmo
};



UCLASS( meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts or player is spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Setter function for the barrel and turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(class UTankBarrel* BarrelToSet, class UTankTurret* TurretToSet);

	// Aims at the location provided by the tank
	void AimAt(FVector HitLocation);

	// Moves the barrel to the desired location
	void MoveBarrel(FVector AimDirection);

	// Returns true if the barrel is moving
	bool IsBarrelMoving();

	// Fires projectile
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "FiringState")
	EFiringState FiringState = EFiringState::Reloading;


private:
	class UTankBarrel* Barrel = nullptr;

	class UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	float ReloadTime = 3;  // the time between two shells fired, in seconds

	double LastFireTime;  // the time the last shell was fired, in seconds

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;
};
