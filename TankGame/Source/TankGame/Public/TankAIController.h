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

private:
	float AcceptanceRadius = 3000;   // how close the AI tank can get to the player
};
