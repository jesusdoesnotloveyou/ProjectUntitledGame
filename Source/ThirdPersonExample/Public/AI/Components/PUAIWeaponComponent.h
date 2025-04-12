// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TPWeaponComponent.h"
#include "PUAIWeaponComponent.generated.h"

class UAnimMontage;

UCLASS()
class THIRDPERSONEXAMPLE_API UPUAIWeaponComponent : public UTPWeaponComponent
{
	GENERATED_BODY()

public:
	// UFUNCTION MACRO for BP using
	// Should remove after AI would be rewritten in CPP
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Attack() override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void HeavyAttack() override;
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void EquipWeapon() override;
	void UnequipWeapon();
	
	bool IsAttackMontagesPlaying() const;
protected:
	virtual void BeginPlay() override;
	
private:

	bool IsMontagesPlaying(const TArray<UAnimMontage*>& AnimMontages) const;
};	
