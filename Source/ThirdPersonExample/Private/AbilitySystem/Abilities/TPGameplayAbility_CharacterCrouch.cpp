// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TPGameplayAbility_CharacterCrouch.h"
#include "Player/TPBaseCharacter.h"

bool UTPGameplayAbility_CharacterCrouch::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;
	
	return ActorInfo->AvatarActor->IsA<ATPBaseCharacter>();
}

void UTPGameplayAbility_CharacterCrouch::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	const auto Character = Cast<ATPBaseCharacter>(OwnerInfo->AvatarActor.Get());
	if (!Character) return;
	Character->Crouch();
}

void UTPGameplayAbility_CharacterCrouch::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	const auto Character = Cast<ATPBaseCharacter>(ActorInfo->AvatarActor.Get());
	if (!Character) return;
	Character->UnCrouch();
}
