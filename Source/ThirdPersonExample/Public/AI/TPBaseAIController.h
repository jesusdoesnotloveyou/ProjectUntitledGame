// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TPBaseAIController.generated.h"

class UTPAIPerceptionComponent;

UCLASS()
class THIRDPERSONEXAMPLE_API ATPBaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATPBaseAIController();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTPAIPerceptionComponent* PUAIPerceptionComponent;

	virtual void OnPossess(APawn* InPawn) override;
};