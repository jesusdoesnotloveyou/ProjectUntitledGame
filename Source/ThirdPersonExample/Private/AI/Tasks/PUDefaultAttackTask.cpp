// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/Tasks/PUDefaultAttackTask.h"
//#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/Components/PUAIWeaponComponent.h"

UPUDefaultAttackTask::UPUDefaultAttackTask()
{
	NodeName = "Default Attack";
}

EBTNodeResult::Type UPUDefaultAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	const auto ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return EBTNodeResult::Failed;

	const auto WeaponComponent = ControlledPawn->GetComponentByClass<UPUAIWeaponComponent>();
	if (!WeaponComponent) return EBTNodeResult::Failed;

	WeaponComponent->Attack();

	// Need some delay to play attack animation
	// and only after that we have to return success status of executing

	return EBTNodeResult::Succeeded;
}