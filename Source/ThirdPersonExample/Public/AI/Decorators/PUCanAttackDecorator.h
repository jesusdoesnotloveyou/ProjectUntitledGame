// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "PUCanAttackDecorator.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UPUCanAttackDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UPUCanAttackDecorator();
protected:
	virtual	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
