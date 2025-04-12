// Project Untitled Game by JDNLY. All Rights Reserved.


#include "AI/Tasks/PUEquipWeaponTask.h"
#include "AIController.h"
#include "AI/Components/PUAIWeaponComponent.h"

UPUEquipWeaponTask::UPUEquipWeaponTask()
{
	NodeName = "Equip Weapon";
}

EBTNodeResult::Type UPUEquipWeaponTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	const auto ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return EBTNodeResult::Failed;
	
	const auto WeaponComponent = ControlledPawn->GetComponentByClass<UPUAIWeaponComponent>();
	if (!WeaponComponent) return EBTNodeResult::Failed;
	if (WeaponComponent->IsWeaponEquiped()) return EBTNodeResult::Succeeded; // or may be succeeded
	
	WeaponComponent->EquipWeapon();
	return EBTNodeResult::Succeeded;
}