// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Menu/PUMenuPlayerController.h"

void APUMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}