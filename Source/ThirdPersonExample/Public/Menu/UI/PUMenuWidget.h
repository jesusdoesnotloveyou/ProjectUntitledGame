// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PUCoreTypes.h"
#include "UI/TPBaseWidget.h"
#include "PUMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UPUGameInstance;

UCLASS()
class THIRDPERSONEXAMPLE_API UPUMenuWidget : public UTPBaseWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* GameOptionsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* SoftWidgetSwitcher;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();
	
	UFUNCTION()
	void OnGameOptions();

	UFUNCTION()
	void OnCredits();

	UPUGameInstance* GetPUGameInstance() const;

	void SetSoftWidgetActive(EPUSoftWidgetType SoftWidgetType);
	EPUSoftWidgetType CurrentSoftWidgetType = EPUSoftWidgetType::None;
};
