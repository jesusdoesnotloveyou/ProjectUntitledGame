// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/Animations/TPWeaponAttackAnimNotifyState.h"
#include "Player/TPBaseCharacter.h"
#include "Components/TPWeaponComponent.h"

void UTPWeaponAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (const auto Player = Cast<ATPBaseCharacter>(MeshComp->GetOwner()))
		if (const auto WeaponComponent = Player->GetComponentByClass<UTPWeaponComponent>())
			WeaponComponent->StartWeaponSwing(DamageTypeClass);
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UTPWeaponAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (const auto Player = Cast<ATPBaseCharacter>(MeshComp->GetOwner()))
		if (const auto WeaponComponent = Player->GetComponentByClass<UTPWeaponComponent>())
			WeaponComponent->StopWeaponSwing();
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
