// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/TPBaseHUD.h"
#include "UI/TPBaseWidget.h"
#include "TPGameModeBase.h"
#include "Engine/Canvas.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPBaseHUD, All, All);

void ATPBaseHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ATPBaseHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EPUGameState::InProgress, CreateWidget<UTPBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EPUGameState::Pause, CreateWidget<UTPBaseWidget>(GetWorld(), PauseHUDWidgetClass));
	GameWidgets.Add(EPUGameState::GameOver, CreateWidget<UTPBaseWidget>(GetWorld(), GameOverHUDWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddUObject(this, &ATPBaseHUD::OnGameStateChanged);
		}
	}
}

void ATPBaseHUD::OnGameStateChanged(EPUGameState NewGameState)
{	
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (GameWidgets.Contains(NewGameState))
	{
		CurrentWidget = GameWidgets[NewGameState];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
