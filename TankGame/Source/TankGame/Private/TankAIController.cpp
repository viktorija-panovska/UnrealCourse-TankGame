#include "TankAIController.h"
#include "Tank.h"



// Called when the game starts or player is spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PossessedTank = GetControlledTank();

	if (!PossessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI controller is not possessing anything"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI controller is possessing: %s"), *(PossessedTank->GetName()));
	}

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank is missing"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is possessing: %s"), *(PlayerTank->GetName()));
	}
}



// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}



// Get the tank the AI controller is possessing
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



// Get the tank possessed by the player controller
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}