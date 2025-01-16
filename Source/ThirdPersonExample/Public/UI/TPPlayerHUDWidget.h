// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TPBaseWidget.h"
#include "Components/TimelineComponent.h"
#include "TPPlayerHUDWidget.generated.h"

// Check the comment in UTPHealthBarWidget

class UProgressBar;
class UImage;

UCLASS()
class THIRDPERSONEXAMPLE_API UTPPlayerHUDWidget : public UTPBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetBackHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* BackHealthProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* BackHealthBarFloatCurve;
	
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	FTimeline BackHealthBarTimeline;

	UFUNCTION()
	void BackHealthBarUpdate(float Alpha);

	void OnNewPawn(APawn* NewPawn);

	void OnHealthChanged(float Health, float HealthDelta);

	float BackHealthBarPercent;
};
