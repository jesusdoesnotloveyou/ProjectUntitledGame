// Project Untitled Game by JDNLY. All Rights Reserved.


#include "AI/TPBaseAIController.h"
#include "AI/Components/TPAIPerceptionComponent.h"
#include "PUAICharacter.h"

ATPBaseAIController::ATPBaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
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