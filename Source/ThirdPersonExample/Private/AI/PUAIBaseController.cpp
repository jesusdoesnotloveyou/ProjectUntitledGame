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
	SetFocus(GetFocusOnActor());
}

void APUAIBaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<APUAICharacter>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}

	PUAIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &APUAIBaseController::OnPerceptionUpdated);
	PUAIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &APUAIBaseController::OnTargetPerceptionUpdated);

	SetState(EPUAIState::Passive);
}

void APUAIBaseController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	UE_LOG(LogTPBaseAIController, Warning, TEXT("OnPerceptionUpdated() called!"));
}

void APUAIBaseController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTPBaseAIController, Warning, TEXT("OnTargetPerceptionUpdated() called!"));
}

void APUAIBaseController::SetState(EPUAIState NewAIState)
{
	if (NewAIState == GetCurrentState()) return;

	if (!GetBlackboardComponent()) return;
	GetBlackboardComponent()->SetValueAsEnum(StateKeyName, static_cast<uint8>(NewAIState));
}

EPUAIState APUAIBaseController::GetCurrentState() const
{
	if (!GetBlackboardComponent()) return EPUAIState::Passive;
	return static_cast<EPUAIState>(GetBlackboardComponent()->GetValueAsEnum(StateKeyName));
}

AActor* APUAIBaseController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(EnemyActorKeyName));
}

bool APUAIBaseController::CanSenseActor(AActor* ActorToSense, EPUAISense SenseType) const
{
	return false;
}
