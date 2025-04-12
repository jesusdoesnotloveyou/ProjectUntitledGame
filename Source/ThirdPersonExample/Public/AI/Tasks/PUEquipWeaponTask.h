// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PUEquipWeaponTask.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UPUEquipWeaponTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPUEquipWeaponTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
