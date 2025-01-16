// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TPAbilitySystemComponent.h"

bool UTPAbilitySystemComponent::TryActivateAbilitiesWithTag(const FGameplayTag& GameplayTag, bool bAllowRemoteActivation /*= true*/)
{
	return TryActivateAbilitiesByTag(FGameplayTagContainer(GameplayTag), bAllowRemoteActivation);
}

bool UTPAbilitySystemComponent::TryCancelAbilitiesWithTag(const FGameplayTag& GameplayTag)
{
	bool Result = false;
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTagContainer(GameplayTag), AbilitiesToActivate, false);

	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbility->K2_CancelAbility();
			Result = true;
		}
	}
	return Result;
}

bool UTPAbilitySystemComponent::IsAbilityActive(const FGameplayTag& GameplayTag) const
{
	bool Result = false;

	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTagContainer(GameplayTag), AbilitiesToActivate, false);

	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			Result |= ActiveAbility->IsActive();
		}
	}
	return Result;
}