// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUExitGameWidget.generated.h"

class UButton;

UCLASS()
class THIRDPERSONEXAMPLE_API UPUExitGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;
	
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnExitGame();
};
