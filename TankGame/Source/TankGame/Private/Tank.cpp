#include "Tank.h"



// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}



// Called when the game starts or player is spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}



float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);   // we don't want to be comparing floats to 0
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}



float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
