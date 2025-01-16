// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TPWeaponComponent.h"
#include "TPAIWeaponComponent.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UTPAIWeaponComponent : public UTPWeaponComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Attack() override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void HeavyAttack() override;
	
	/*UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void EquipWeapon() override;*/
	
protected:
	virtual void BeginPlay() override;
};	
