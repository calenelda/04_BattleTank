// Copyright Michal Jasinski 2018

#include "TankPlayerController.h"


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

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	// Get world location through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}

