// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/TPPlayerHUDWidget.h"
#include "Components/TPHealthComponent.h"
#include "Components/ProgressBar.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPPlayerHUDWidget, All, All);

void UTPPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UTPPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}

	if (BackHealthBarFloatCurve)
	{
		FOnTimelineFloat BackHealthBarUpdate;
		BackHealthBarUpdate.BindUFunction(this, FName("BackHealthBarUpdate"));
		BackHealthBarTimeline.AddInterpFloat(BackHealthBarFloatCurve, BackHealthBarUpdate);
		BackHealthBarTimeline.SetLooping(false);
	}
}

void UTPPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	if (!NewPawn) return;
	const auto HealthComponent = NewPawn->GetComponentByClass<UTPHealthComponent>();
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UTPPlayerHUDWidget::OnHealthChanged);
	}
}

void UTPPlayerHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	BackHealthBarTimeline.TickTimeline(InDeltaTime);

}

void UTPPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta > 0 || FMath::IsNearlyZero(HealthDelta))
	{
		BackHealthProgressBar->SetPercent(GetHealthPercent());
	}
	else {
		BackHealthBarPercent = BackHealthProgressBar->GetPercent();
		BackHealthBarTimeline.PlayFromStart();
	}
}

void UTPPlayerHUDWidget::BackHealthBarUpdate(float Alpha)
{
	BackHealthBarPercent = FMath::Lerp(BackHealthBarPercent, GetHealthPercent(), Alpha);
	BackHealthProgressBar->SetPercent(BackHealthBarPercent);
}

float UTPPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto HealthComponent = Player->GetComponentByClass<UTPHealthComponent>();
	if (!HealthComponent) return 0.0f;
	
	return HealthComponent->GetHealthPercent();
}

float UTPPlayerHUDWidget::GetBackHealthPercent() const
{
	return BackHealthBarPercent;
}

bool UTPPlayerHUDWidget::IsPlayerAlive() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return false;

	const auto HealthComponent = Player->GetComponentByClass<UTPHealthComponent>();
	
	return HealthComponent && !HealthComponent->IsDead();
}

