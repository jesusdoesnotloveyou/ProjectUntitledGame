// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/Animations/TPSaveAttackAnimNotify.h"

void UTPSaveAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnSaveAttackNotified.Broadcast();
	Super::Notify(MeshComp, Animation, EventReference);
}