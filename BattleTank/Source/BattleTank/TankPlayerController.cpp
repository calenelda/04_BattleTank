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

	FVector HitLocation;
	// Get world location through crosshair
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);

	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// GetLookVectorHitLocation
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector worldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		worldLocation, 
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult hitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LineTraceRange * LookDirection;
	if(GetWorld()->LineTraceSingleByChannel(
			hitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility
		))
	{
		HitLocation = hitResult.Location;
		return true;
	} else {
		HitLocation = FVector::ZeroVector;
		return false;
	}
	
}
