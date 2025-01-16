// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/Animations/TPResetComboAnimNotify.h"

void UTPResetComboAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnResetComboNotified.Broadcast();
	Super::Notify(MeshComp, Animation, EventReference);
}