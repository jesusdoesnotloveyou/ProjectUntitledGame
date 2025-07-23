// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/Decorators/PUCanEquipDecorator.h"
#include "AIController.h"
#include "AI/Components/PUAIWeaponComponent.h"

UPUCanEquipDecorator::UPUCanEquipDecorator()
{
	NodeName = "Can Equip";
}

bool UPUCanEquipDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller || !Controller->GetPawn()) return false;

	const auto WeaponComponent = Controller->GetPawn()->GetComponentByClass<UPUAIWeaponComponent>();
	if (!WeaponComponent) return false;

	return !WeaponComponent->IsEquipAnimInProgress();
}