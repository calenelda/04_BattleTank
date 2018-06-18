// Copyright Michal Jasinski 2018

#include "TankAIController.h"

void ATankAIController::BeginPlay()  {
	Super::BeginPlay();

	auto tank = GetControlledTank();
	if (!tank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing %s"), *(tank->GetName()))
	}

	auto playerTank = GetPlayerTank();
	if (playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s found %s as it's target."), *GetName(), *(playerTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s has no target."), *GetName())
	}

}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerController = GetWorld()->GetFirstPlayerController();
	if (playerController == nullptr) {
		return nullptr;
	}

	auto playerTank = playerController->GetPawn();
	if (playerTank == nullptr) {
		return nullptr;
	}

	return Cast<ATank>(playerTank);
}


