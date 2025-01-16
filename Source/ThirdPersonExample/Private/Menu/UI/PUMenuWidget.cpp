// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Menu/UI/PUMenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "PUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogPUMenuWidget, All, All);

void UPUMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UPUMenuWidget::OnStartGame);
	}

	if (GameOptionsButton)
	{
		GameOptionsButton->OnClicked.AddDynamic(this, &UPUMenuWidget::OnGameOptions);
	}

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UPUMenuWidget::OnCredits);
	}
}

void UPUMenuWidget::OnStartGame()
{
	const auto PUGameInstance = GetPUGameInstance();
	if (!PUGameInstance) return;

	UGameplayStatics::OpenLevel(this, PUGameInstance->GetCoreLevelName());
}

UPUGameInstance* UPUMenuWidget::GetPUGameInstance() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<UPUGameInstance>();
}

void UPUMenuWidget::SetSoftWidgetActive(EPUSoftWidgetType SoftWidgetType)
{
	UE_LOG(LogPUMenuWidget, Warning, TEXT("Soft Widget Type: %i"), static_cast<int32>(CurrentSoftWidgetType))
	if (SoftWidgetType == CurrentSoftWidgetType)
	{
		CurrentSoftWidgetType = EPUSoftWidgetType::None;
	}
	else
	{
		CurrentSoftWidgetType = SoftWidgetType;
	}
	SoftWidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(CurrentSoftWidgetType));
}

void UPUMenuWidget::OnGameOptions()
{
	SetSoftWidgetActive(EPUSoftWidgetType::Options);
	UE_LOG(LogPUMenuWidget, Warning, TEXT("Options clicked"));
}

void UPUMenuWidget::OnCredits()
{
	SetSoftWidgetActive(EPUSoftWidgetType::Credits);
	UE_LOG(LogPUMenuWidget, Warning, TEXT("Credits clicked"));
}