// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/PUOpenOptionsWidget.h"
#include "Components/Button.h"

void UPUOpenOptionsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (OpenOptionsButton)
	{
		OpenOptionsButton->OnClicked.AddDynamic(this, &UPUOpenOptionsWidget::OnOpenOptions);
	}
}

void UPUOpenOptionsWidget::OnOpenOptions()
{

}
