#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"



UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()


private:
	// Sets default values for this pawn's properties
	ATank();


protected:
	// Called when the game starts or player is spawned
	virtual void BeginPlay() override;


public:	
	// Aims at the location provided by the tank controller
	void AimAt(FVector HitLocation);

	// Fires projectile
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	class UTankAimingComponent* TankAimingComponent = nullptr;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	class UTankBarrel* Barrel = nullptr;   // local barrel reference

	float ReloadTime = 3;  // the time between two shells fired, in seconds

	double LastFireTime;  // the time the last shell was fired, in seconds
};