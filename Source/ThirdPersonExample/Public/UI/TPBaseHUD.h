// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PUCoreTypes.h"
#include "GameFramework/HUD.h"
#include "TPBaseHUD.generated.h"

class UTPBaseWidget;

UCLASS()
class THIRDPERSONEXAMPLE_API ATPBaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

protected:
	// Main widgets
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseHUDWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverHUDWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EPUGameState, UTPBaseWidget*> GameWidgets;

	UPROPERTY()
	UTPBaseWidget* CurrentWidget = nullptr;

	void OnGameStateChanged(EPUGameState NewGameState);
};
