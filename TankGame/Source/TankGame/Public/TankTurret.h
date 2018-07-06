#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"



UCLASS( meta = (BlueprintSpawnableComponent) )
class TANKGAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	void Rotate(float RelativeSpeed);
	

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreePerSecond = 25;
};
