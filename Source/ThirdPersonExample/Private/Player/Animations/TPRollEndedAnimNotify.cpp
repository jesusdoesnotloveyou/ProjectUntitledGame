// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/Animations/TPRollEndedAnimNotify.h"

void UTPRollEndedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnRollEndNotified.Broadcast();
	Super::Notify(MeshComp, Animation, EventReference);
}
