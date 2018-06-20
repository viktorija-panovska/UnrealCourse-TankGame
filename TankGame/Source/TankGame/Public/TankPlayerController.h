#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Tank.h"
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


private:
	// Get the tank the controller is possessing
	ATank* GetControlledTank() const;

	// Move the tank barrel to aim at the crosshair on the UI
	void AimTowardsCrosshair();

	// Return true if the crosshair is aiming at the terrain
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	// De-projecting the screen position of the crosshair to a world direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;



private:
	UPROPERTY(EditAnywhere, Category = "CrosshairPosition")
	float CrosshairLocationX = 0.5;

	UPROPERTY(EditAnywhere, Category = "CrosshairPosition")
	float CrosshairLocationY = 0.3333333;

};
