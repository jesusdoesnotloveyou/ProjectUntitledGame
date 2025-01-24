// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/Animations/TPWeaponAttackAnimNotifyState.h"
#include "Components/TPWeaponComponent.h"

void UTPWeaponAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		const auto WeaponComponent = MeshComp->GetOwner()->GetComponentByClass<UTPWeaponComponent>();
		if (WeaponComponent)
		{
			WeaponComponent->StartWeaponSwing(DamageTypeClass);
		}
	}
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UTPWeaponAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		const auto WeaponComponent = MeshComp->GetOwner()->GetComponentByClass<UTPWeaponComponent>();
		if (WeaponComponent)
		{
			WeaponComponent->StopWeaponSwing();
		}
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
