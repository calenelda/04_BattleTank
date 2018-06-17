// Copyright Michal Jasinski 2018

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto tank = GetControlledTank();
	if (!tank) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possesing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possesing %s"), *(tank->GetName()))
	}
	
}

