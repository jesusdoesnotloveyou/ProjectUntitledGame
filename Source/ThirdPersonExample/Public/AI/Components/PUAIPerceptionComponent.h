// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "PUAIPerceptionComponent.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UPUAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	UPUAIPerceptionComponent();

	AActor* GetClosestEnemy() const;
};
