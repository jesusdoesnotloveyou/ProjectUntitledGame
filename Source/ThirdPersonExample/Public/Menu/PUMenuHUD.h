// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "PUMenuHUD.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API APUMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	virtual void BeginPlay() override;
};
