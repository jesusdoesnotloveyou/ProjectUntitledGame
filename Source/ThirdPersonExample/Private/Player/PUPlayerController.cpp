// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/PUPlayerController.h"
#include "TPGameModeBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//#include "Components/PURespawnComponent.h"

APUPlayerController::APUPlayerController()
{
	//RespawnComponent = CreateDefaultSubobject<UPURespawnComponent>("RespawnComponent");
}

void APUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->OnGameStateChanged.AddUObject(this, &APUPlayerController::OnGameStateChanged);
	}
}

void APUPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OnNewPawn.Broadcast(InPawn);
}

void APUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	// Should rewrite with enhanced input
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &APUPlayerController::OnPauseGame);
}

void APUPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void APUPlayerController::OnGameStateChanged(EPUGameState NewGameState)
{
	if (NewGameState == EPUGameState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}