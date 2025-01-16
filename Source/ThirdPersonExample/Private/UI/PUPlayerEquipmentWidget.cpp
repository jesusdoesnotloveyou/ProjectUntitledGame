// Project Untitled Game by JDNLY. All Rights Reserved.

#include "UI/PUPlayerEquipmentWidget.h"
#include "Components/TPHealthComponent.h"

void UPUPlayerEquipmentWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

int32 UPUPlayerEquipmentWidget::GetNumberOfPotions() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0;

	const auto HealthComponent = Player->GetComponentByClass<UTPHealthComponent>();
	if (!HealthComponent) return 0;

	return HealthComponent->GetNumberOfPotions();
}
