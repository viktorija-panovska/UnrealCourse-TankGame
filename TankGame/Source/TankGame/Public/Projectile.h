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

	
public:
	void LaunchProjectile(float ProjectileSpeed);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();


private:
	class UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Destroy")
	float DestroyDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float ProjectileDamage = 20.f;
};
