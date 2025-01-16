// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/TPBaseWidget.h"

void UTPBaseWidget::Show()
{
	// because no (meta = BindAnimation)
	if (WidgetAnimation)
	{
		PlayAnimation(WidgetAnimation);
	}
}
