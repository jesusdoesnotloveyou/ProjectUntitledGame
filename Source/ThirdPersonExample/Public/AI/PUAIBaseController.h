// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PUCoreTypes.h"
#include "PUAIBaseController.generated.h"

class UPUAIPerceptionComponent;
struct FAIStimulus;

UCLASS()
class THIRDPERSONEXAMPLE_API APUAIBaseController : public AAIController
{
	GENERATED_BODY()
	
public:
	APUAIBaseController();

	virtual void Tick(float DeltaTime) override;

	EPUAIState GetCurrentState() const;
	void SetState(EPUAIState NewAIState);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPUAIPerceptionComponent* PUAIPerceptionComponent;

	virtual void OnPossess(APawn* InPawn) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | Key Name")
	FName EnemyActorKeyName = "EnemyActor";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | Key Name")
	FName StateKeyName = "State";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | Key Name")
	FName  AimLocationKeyName = "AimLocation";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | Key Name")
	FName  AttackRadiusKeyName = "AttackRadius";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | Key Name")
	FName  DefendRadiusKeyName = "DefendRadius";

private:
	AActor* GetFocusOnActor() const;

	bool CanSenseActor(AActor* ActorToSense, EPUAISense SenseType) const;
	
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};