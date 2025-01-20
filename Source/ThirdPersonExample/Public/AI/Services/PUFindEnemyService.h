// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PUFindEnemyService.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UPUFindEnemyService : public UBTService
{
	GENERATED_BODY()
	
public:
	UPUFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
