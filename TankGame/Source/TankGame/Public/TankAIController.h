#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;


public:
	// Get the tank the AI controller is possessing
	ATank* GetPossessedTank() const;

	// Get the tank possessed by the player controller
	ATank* GetPlayerTank() const;
};
