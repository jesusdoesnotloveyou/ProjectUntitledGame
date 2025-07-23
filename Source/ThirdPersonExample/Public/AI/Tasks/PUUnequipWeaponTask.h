// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PUUnequipWeaponTask.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UPUUnequipWeaponTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPUUnequipWeaponTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
