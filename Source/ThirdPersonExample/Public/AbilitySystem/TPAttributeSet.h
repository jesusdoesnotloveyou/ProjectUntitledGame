// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TPAttributeSet.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UTPAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	/** Sample "Health" Attribute, publicly accessible */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	
public:
	//~ Helper functions for "Health" attribute
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UTPAttributeSet, Health);
	//GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	float GetHealth() const;
	void SetHealth(float NewHealth);
	//GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
