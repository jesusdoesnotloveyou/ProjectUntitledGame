// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "PUOpenOptionsWidget.generated.h"

class UButton;

// Unused widget for now
UCLASS()
class THIRDPERSONEXAMPLE_API UPUOpenOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* OpenOptionsButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnOpenOptions();
};
