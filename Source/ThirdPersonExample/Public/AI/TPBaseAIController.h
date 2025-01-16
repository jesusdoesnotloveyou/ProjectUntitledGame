// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TPBaseAIController.generated.h"

class UAIPerceptionComponent;

UCLASS()
class THIRDPERSONEXAMPLE_API ATPBaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATPBaseAIController();

protected:
	UAIPerceptionComponent* AIPerceptionComponent;

	virtual void OnPossess(APawn* InPawn) override;
};
