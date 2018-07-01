#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.h"
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
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// Aiming at the location provided by the tank controller
	void AimAt(FVector HitLocation);

	// Setting up the barrel
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);


protected:
	UTankAimingComponent* TankAimingComponent = nullptr;


private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 100000;  // TODO find sensible starting value
};