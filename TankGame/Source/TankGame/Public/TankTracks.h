#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"



UCLASS( meta = (BlueprintSpawnableComponent) )
class TANKGAME_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UTankTracks();

	virtual void BeginPlay() override;

	void DriveTracks();

	void ApplySidewaysForce(float DeltaTime);

	void SetTrackThrottle(float Throttle);


private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


private:
	UPROPERTY(EditDefaultsOnly)
	float TankMaxDrivingForce = 4000;  // assume the 40 ton tank has an acceleration of 1G

	float CurrentThrottle = 0;
};
