// Copyright Michal Jasinski 2018

#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()  {
	Super::BeginPlay();

	auto tank = GetControlledTank();
	if (!tank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing %s"), *(tank->GetName()))
	}
}


