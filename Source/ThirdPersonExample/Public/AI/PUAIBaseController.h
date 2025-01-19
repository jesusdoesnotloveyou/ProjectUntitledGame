// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PUAIBaseController.generated.h"

class UPUAIPerceptionComponent;

UCLASS()
class THIRDPERSONEXAMPLE_API APUAIBaseController : public AAIController
{
	GENERATED_BODY()
	
public:
	APUAIBaseController();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPUAIPerceptionComponent* PUAIPerceptionComponent;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName EnemyActorKeyName = "EnemyActor";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName StateKeyName = "State";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName  AimLocationKeyName = "AimLocation";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName  AttackRadiusKeyName = "AimLocation";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName  DefendRadiusKeyName = "AimLocation";

private:
	AActor* GetFocusOnActor() const;

};