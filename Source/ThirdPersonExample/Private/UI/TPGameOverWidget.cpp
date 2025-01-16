// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/TPGameOverWidget.h"
#include "TPGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UTPGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStateChanged.AddUObject(this, &UTPGameOverWidget::OnGameStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &UTPGameOverWidget::OnResetLevel);
    }
}

void UTPGameOverWidget::OnGameStateChanged(EPUGameState NewGameState)
{
    if (NewGameState == EPUGameState::GameOver)
    {
        Show();
    }
}

void UTPGameOverWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}