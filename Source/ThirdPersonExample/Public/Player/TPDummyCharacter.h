// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/TPBaseCharacter.h"
#include "Interfaces/CombatSystem/Attackable.h"
#include "TPDummyCharacter.generated.h"

class UWidgetComponent;
class UBehaviorTree;

UCLASS()
class THIRDPERSONEXAMPLE_API ATPDummyCharacter : public ATPBaseCharacter, public IDamagable
{
	GENERATED_BODY()

public:
	ATPDummyCharacter(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* LockOnWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	float HealthVisibilityDistance = 1000.0f;

	virtual void BeginPlay() override;
	
	virtual void OnHealthChanged(float Health, float HealthDelta) override;
	virtual void OnDeath() override;

private:
	virtual void UpdateHealthBarVisibility();
	virtual void UpdateTargetVisibility();
};
