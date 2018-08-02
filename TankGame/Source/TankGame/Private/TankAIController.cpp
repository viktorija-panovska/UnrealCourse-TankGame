#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"



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
	AimingComponent->Fire();
}