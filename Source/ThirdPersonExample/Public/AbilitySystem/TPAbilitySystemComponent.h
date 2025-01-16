// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TPAbilitySystemComponent.generated.h"

struct FGameplayTag;

UCLASS()
class THIRDPERSONEXAMPLE_API UTPAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool TryActivateAbilitiesWithTag(const FGameplayTag& GameplayTag, bool bAllowRemoteActivation = true);
	
	bool TryCancelAbilitiesWithTag(const FGameplayTag& GameplayTag);
	
	bool IsAbilityActive(const FGameplayTag& GameplayTag) const;
};