// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "PUCanEquipDecorator.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UPUCanEquipDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UPUCanEquipDecorator();
protected:
	virtual	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};