#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"



UCLASS( meta = (BlueprintSpawnableComponent) )
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	

public:
	// Setter function for the tracks
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(class UTankTracks* RightTrackToSet, class UTankTracks* LeftTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveForward(float Throttle);
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveBackward(float Throttle);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveRight(float Throttle);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveLeft(float Throttle);


private:
	// Controls the movement of the AI controller - connects to MoveToActor()
	// Called from the pathfinding logic by the AI controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


private:
	class UTankTracks* RightTrack;

	class UTankTracks* LeftTrack;
};