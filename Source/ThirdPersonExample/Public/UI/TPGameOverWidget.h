// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/TPBaseWidget.h"
#include "PUCoreTypes.h"
#include "TPGameOverWidget.generated.h"

class UButton;

UCLASS()
class THIRDPERSONEXAMPLE_API UTPGameOverWidget : public UTPBaseWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

	virtual void NativeOnInitialized() override;
	
private:
	void OnGameStateChanged(EPUGameState NewGameState);

	UFUNCTION()
	void OnResetLevel();
};
