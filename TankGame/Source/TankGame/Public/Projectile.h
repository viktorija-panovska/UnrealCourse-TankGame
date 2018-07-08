#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"



UCLASS()
class TANKGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AProjectile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
public:
	void LaunchProjectile(float ProjectileSpeed);


private:
	class UProjectileMovementComponent* ProjectileMovement = nullptr;
	
};
