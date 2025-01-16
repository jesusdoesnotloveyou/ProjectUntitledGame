// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/TPHealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "TPHealthComponent.h"

void UTPHealthBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BackHealthBarFloatCurve)
	{
		FOnTimelineFloat BackHealthBarUpdate;
		BackHealthBarUpdate.BindUFunction(this, FName("BackHealthBarUpdate"));
		BackHealthBarTimeline.AddInterpFloat(BackHealthBarFloatCurve, BackHealthBarUpdate);
		BackHealthBarTimeline.SetLooping(false);
	}
}

void UTPHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	BackHealthBarTimeline.TickTimeline(InDeltaTime);

}

void UTPHealthBarWidget::BackHealthBarUpdate(float Alpha)
{
	BackHealthBarPercent = FMath::Lerp(BackHealthBarPercent, GetHealthPercent(), Alpha);
	BackHealthProgressBar->SetPercent(BackHealthBarPercent);
}

float UTPHealthBarWidget::GetHealthPercent() const
{
	return HealthBarPercent;
}

float UTPHealthBarWidget::GetBackHealthPercent() const
{
	return BackHealthBarPercent;
}

void UTPHealthBarWidget::SetHealthPercent(float Percent, float Health, float HealthDelta)
{
	HealthBarPercent = Percent;

	if (!HealthProgressBar) return;
	const auto HealthBarVisibility = (Percent > PercentVisibilityTheshold || FMath::IsNearlyZero(Percent)) ?
		ESlateVisibility::Hidden : ESlateVisibility::Visible;
	
	HealthProgressBar->SetVisibility(HealthBarVisibility);
	BackHealthProgressBar->SetVisibility(HealthBarVisibility);
	HealthProgressBar->SetPercent(Percent);
	
	if (HealthDelta > 0 || FMath::IsNearlyZero(HealthDelta))
	{
		BackHealthProgressBar->SetPercent(GetHealthPercent());
	}
	else {
		BackHealthBarPercent = BackHealthProgressBar->GetPercent();
		BackHealthBarTimeline.PlayFromStart();
	}
}
