// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/TPBaseAIController.h"
#include "AI/Components/TPAIPerceptionComponent.h"
#include "AI/PUAICharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPBaseAIController, All, All);

ATPBaseAIController::ATPBaseAIController()
{
	PUAIPerceptionComponent = CreateDefaultSubobject<UTPAIPerceptionComponent>("PUPerceptionComponent");
	SetPerceptionComponent(*PUAIPerceptionComponent);
}

void ATPBaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto AimActor = PUAIPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor);
}

void ATPBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<APUAICharacter>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}