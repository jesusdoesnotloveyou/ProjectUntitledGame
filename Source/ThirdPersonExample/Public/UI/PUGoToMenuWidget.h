// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUGoToMenuWidget.generated.h"

class UPUGameInstance;
class UButton;

UCLASS()
class THIRDPERSONEXAMPLE_API UPUGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* GoToMenuButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnGoToMenu();
	UPUGameInstance* GetPUGameInstance() const;
};
