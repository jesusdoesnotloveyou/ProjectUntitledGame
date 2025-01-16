// Fill out your copyright notice in the Description page of Project Settings.


#include "TPAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

float UTPAttributeSet::GetHealth() const
{
	return FMath::Max(Health.GetCurrentValue(), 0.0f);
}

void UTPAttributeSet::SetHealth(float NewHealth)
{
	NewHealth = FMath::Max(NewHealth, 0.0f);

	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if(ensure(ASC))
	{
		ASC->SetNumericAttributeBase(GetHealthAttribute(), NewHealth);
	}
}

void UTPAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Max(GetHealth(), 0.0f));
	}
}

void UTPAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTPAttributeSet, Health, OldHealth);
}

void UTPAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTPAttributeSet, Health, COND_None, REPNOTIFY_Always);
}