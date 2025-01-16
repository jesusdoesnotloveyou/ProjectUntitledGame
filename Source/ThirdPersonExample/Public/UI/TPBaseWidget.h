// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPBaseWidget.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UTPBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Show();

protected:
	UPROPERTY(/*meta = (BindAnimation),*/ Transient)
	UWidgetAnimation* WidgetAnimation;
};