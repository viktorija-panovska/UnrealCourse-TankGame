#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"



// Called when the game starts or player is spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}



// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move to the player tank
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim at the player tank
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}



void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}



void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	
	GetPawn()->DetachFromControllerPendingDestroy();
}