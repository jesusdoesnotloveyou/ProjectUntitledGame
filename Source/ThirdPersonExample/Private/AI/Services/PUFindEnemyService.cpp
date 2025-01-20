// Project Untitled Game by JDNLY. All Rights Reserved.


#include "AI/Services/PUFindEnemyService.h"
#include "AI/Components/PUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UPUFindEnemyService::UPUFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UPUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Controller ? Controller->GetComponentByClass<UPUAIPerceptionComponent>() : nullptr;
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}