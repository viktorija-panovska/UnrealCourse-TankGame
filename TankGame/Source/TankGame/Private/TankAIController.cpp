#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	auto PossessedTank = GetPossessedTank();

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


ATank* ATankAIController::GetPossessedTank() const
{
	return Cast<ATank>(GetPawn());
}


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