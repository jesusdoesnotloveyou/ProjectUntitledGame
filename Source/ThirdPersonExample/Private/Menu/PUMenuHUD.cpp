// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Menu/PUMenuHUD.h"
#include "UI/TPBaseWidget.h"

void APUMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UTPBaseWidget>(GetWorld(), MenuWidgetClass);
		MenuWidget->AddToViewport();
		MenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}