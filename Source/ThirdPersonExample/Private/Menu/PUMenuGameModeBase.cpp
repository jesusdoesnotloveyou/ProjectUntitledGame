// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Menu/PUMenuGameModeBase.h"
#include "Menu/PUMenuHUD.h"
#include "Menu/PUMenuPlayerController.h"

APUMenuGameModeBase::APUMenuGameModeBase()
{
	PlayerControllerClass = APUMenuPlayerController::StaticClass();
	HUDClass = APUMenuHUD::StaticClass();
}