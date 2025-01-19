// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/PUAIBaseController.h"
#include "AI/Components/PUAIPerceptionComponent.h"
#include "AI/PUAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPBaseAIController, All, All);

APUAIBaseController::APUAIBaseController()
{
	PUAIPerceptionComponent = CreateDefaultSubobject<UPUAIPerceptionComponent>("PUPerceptionComponent");
	SetPerceptionComponent(*PUAIPerceptionComponent);
}

void APUAIBaseController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APUAIBaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<APUAICharacter>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}

AActor* APUAIBaseController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(EnemyActorKeyName));
}