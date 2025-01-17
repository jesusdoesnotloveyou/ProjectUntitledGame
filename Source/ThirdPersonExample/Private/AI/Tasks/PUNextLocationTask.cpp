// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/Tasks/PUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UPUNextLocationTask::UPUNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type UPUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return EBTNodeResult::Failed;

	const auto NavSystem = UNavigationSystemV1::GetCurrent(ControlledPawn);
	if (!NavSystem) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	const auto IsLocationFound = NavSystem->GetRandomReachablePointInRadius(ControlledPawn->GetNavAgentLocation(), MaxRadiusLocation, NavLocation);
	if (!IsLocationFound) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}