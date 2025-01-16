// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "TPHealthBarWidget.generated.h"

class UProgressBar;

// Future work
// This class copies almost all logic from TPPlayerHUDWidget.h, so it might be a good idea to create interface-like class
// for Health Widget, that can be used in PlayerCharacter class as well as EnemyCharacter (or maybe even in BaseCharacter,
// because all characters use the logic of HealthWidget)

UCLASS()
class THIRDPERSONEXAMPLE_API UTPHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	float PercentVisibilityTheshold = 0.95f;

	void SetHealthPercent(float Percent, float Health, float HealthDelta);

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetBackHealthPercent() const;

protected:
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

	float BackHealthBarPercent;
	float HealthBarPercent;
};