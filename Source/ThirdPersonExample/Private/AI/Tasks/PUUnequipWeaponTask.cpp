// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/Tasks/PUUnequipWeaponTask.h"
#include "AIController.h"
#include "AI/Components/PUAIWeaponComponent.h"

UPUUnequipWeaponTask::UPUUnequipWeaponTask()
{
	NodeName = "Unequip Weapon";
}

EBTNodeResult::Type UPUUnequipWeaponTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	const auto ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return EBTNodeResult::Failed;

	const auto WeaponComponent = ControlledPawn->GetComponentByClass<UPUAIWeaponComponent>();
	if (!WeaponComponent) return EBTNodeResult::Failed;
	if (!WeaponComponent->IsWeaponEquiped()) return EBTNodeResult::Succeeded;
	
	WeaponComponent->UnequipWeapon();
	return EBTNodeResult::Succeeded;
}
