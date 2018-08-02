#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"



UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or player is spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get the tank the controller is possessing
	UFUNCTION(BlueprintCallable, Category = "Setup")
	class ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(class UTankAimingComponent* AimingComponentReference);


private:
	// Move the tank barrel to aim at the crosshair on the UI
	void AimTowardsCrosshair();

	// Return true if the crosshair is aiming at the terrain
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	// De-projecting the screen position of the crosshair to a world direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

	// Line-tracing through the crosshair
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;


private:
	UPROPERTY(EditDefaultsOnly, Category = "CrosshairPosition")
	float CrosshairLocationX = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "CrosshairPosition")
	float CrosshairLocationY = 0.3333333;

	UPROPERTY(EditDefaultsOnly, Category = "LineTrace")
	float LineTraceRange = 1000000;
};
