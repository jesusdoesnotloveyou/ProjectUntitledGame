// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/TPBaseWidget.h"
#include "PUPauseWidget.generated.h"

class UButton;

UCLASS()
class THIRDPERSONEXAMPLE_API UPUPauseWidget : public UTPBaseWidget
{
	GENERATED_BODY()
		
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

private:
	UFUNCTION()
	void OnClearPause();
};
