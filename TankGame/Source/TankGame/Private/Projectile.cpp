#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AProjectile::LaunchProjectile(float ProjectileSpeed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * ProjectileSpeed);  // When we spawn the projectile, we set the location and rotation the same as the barrel, so this will be the barrel's forward vector
	ProjectileMovement->Activate();
}