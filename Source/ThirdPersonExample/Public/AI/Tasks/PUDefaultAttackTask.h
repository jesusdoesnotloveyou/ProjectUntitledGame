// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PUDefaultAttackTask.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UPUDefaultAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPUDefaultAttackTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
};
