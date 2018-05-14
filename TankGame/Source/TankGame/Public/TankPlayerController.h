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
};
