#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"



UCLASS( meta = (BlueprintSpawnableComponent) )
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	void Elevate(float RelativeSpeed);


private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreePerSecond = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevation = 40;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevation = 0;
};
