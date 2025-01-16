// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/PUExitGameWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UPUExitGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UPUExitGameWidget::OnExitGame);
	}
}

void UPUExitGameWidget::OnExitGame()
{
	if (!GetWorld()) return;
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
