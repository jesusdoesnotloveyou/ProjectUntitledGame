// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/PUPauseWidget.h"
#include "Components/Button.h"
#include "Gameframework/GameModeBase.h"
#include "PUOpenOptionsWidget.h"

bool UPUPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UPUPauseWidget::OnClearPause);
    }
    return InitStatus;
}

void UPUPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}