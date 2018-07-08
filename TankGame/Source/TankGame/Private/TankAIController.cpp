#include "TankAIController.h"
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


	auto ControlledTank = Cast<ATank>(GetPawn());

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());


	if (PlayerTank)
	{
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire();
	}
}