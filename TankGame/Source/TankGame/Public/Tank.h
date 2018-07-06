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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// Sets up the barrel
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(class UTankBarrel* BarrelToSet);

	// Sets up the turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurretReference(class UTankTurret* TurretToSet);
	
	// Aims at the location provided by the tank controller
	void AimAt(FVector HitLocation);


protected:
	class UTankAimingComponent* TankAimingComponent = nullptr;


private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 100000;
};