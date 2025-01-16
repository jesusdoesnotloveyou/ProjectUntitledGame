// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/Animations/TPEquipWeaponAnimNotify.h"

void UTPEquipWeaponAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnWeaponEquipedNotified.Broadcast();
	Super::Notify(MeshComp, Animation, EventReference);
}
