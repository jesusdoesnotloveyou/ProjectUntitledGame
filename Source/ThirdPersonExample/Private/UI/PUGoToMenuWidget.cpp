// Project Untitled Game by JDNLY. All Rights Reserved.


#include "UI/PUGoToMenuWidget.h"
#include "Components/Button.h"
#include "PUGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPUGoToMenuWidget, All, All);

void UPUGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UPUGoToMenuWidget::OnGoToMenu);
	}
}

void UPUGoToMenuWidget::OnGoToMenu()
{
	const auto PUGameInstance = GetPUGameInstance();
	if (!PUGameInstance) return;
	
	if (PUGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogPUGoToMenuWidget, Warning, TEXT("Menu level name is NONE"));
		return;
	}
	UGameplayStatics::OpenLevel(this, PUGameInstance->GetMenuLevelName());
}

UPUGameInstance* UPUGoToMenuWidget::GetPUGameInstance() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<UPUGameInstance>();
}