// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PUGameInstance.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UPUGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FName GetCoreLevelName() const { return CoreLevelName; }
	FName GetMenuLevelName() const { return MenuLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName CoreLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName CoreLevelDisplayName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	UTexture2D* LevelThumb;
};
