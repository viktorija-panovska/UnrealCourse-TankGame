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
};