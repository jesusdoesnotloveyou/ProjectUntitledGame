// Project Untitled Game by JDNLY. All Rights Reserved.

#include "TPGameModeBase.h"
#include "Player/TPPlayerCharacter.h"
#include "Player/PUPlayerController.h"
#include "UI/TPBaseHUD.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPGameModeBase, All, All);

ATPGameModeBase::ATPGameModeBase()
{
	DefaultPawnClass = ATPPlayerCharacter::StaticClass();
	PlayerControllerClass = APUPlayerController::StaticClass();
	HUDClass = ATPBaseHUD::StaticClass();
}

void ATPGameModeBase::StartPlay()
{
	Super::StartPlay();

    if (GetWorld() 
        && GetWorld()->GetFirstPlayerController()
        && GetWorld()->GetFirstPlayerController()->GetPawn())
    {
        const auto PC = Cast<ATPPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
        if (PC)
        {
            PC->OnPlayerCharacterDeath.AddUObject(this, &ATPGameModeBase::GameOver);
        }
    }
	SetGameState(EPUGameState::InProgress);
}

void ATPGameModeBase::SetGameState(EPUGameState NewGameState)
{
	if (GameState == NewGameState) return;

	GameState = NewGameState;
	OnGameStateChanged.Broadcast(GameState);
}

bool ATPGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    UE_LOG(LogTPGameModeBase, Warning, TEXT("SetPause() from derived gamemode class called"));
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (PauseSet)
    {
        SetGameState(EPUGameState::Pause);
    }
    return PauseSet;
}

bool ATPGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        UE_LOG(LogTPGameModeBase, Warning, TEXT("ClearPause() from derived gamemode class called"));
        SetGameState(EPUGameState::InProgress);
    }
    return PauseCleared;
}

void ATPGameModeBase::GameOver()
{
    UE_LOG(LogTPGameModeBase, Error, TEXT("-----GAME OVER -----"));
    
    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(Cast<APlayerController>(Pawn->GetController()));
        }
    }
    SetGameState(EPUGameState::GameOver);
}