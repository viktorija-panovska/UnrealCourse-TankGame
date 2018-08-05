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

	virtual void SetPawn(APawn* InPawn) override;


private:
	UFUNCTION()
	void OnPossessedTankDeath();


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float AcceptanceRadius = 8000;   // how close the AI tank can get to the player
};
