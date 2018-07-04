#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "AIController.h"
#include "TankAIController.generated.h"



UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or player is spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// Get the tank the AI controller is possessing
	class ATank* GetControlledTank() const;

	// Get the tank possessed by the player controller
	class ATank* GetPlayerTank() const;
};
