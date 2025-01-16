// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/Animations/TPRotationAnimNotifyState.h"
#include "Player/TPBaseCharacter.h"
#include "Components/TPBaseCharacterMovementComponent.h"

void UTPRotationAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (const auto Player = Cast<ATPBaseCharacter>(MeshComp->GetOwner()))
		if (const auto BaseCharacterMovement = Player->GetBaseCharacterMovement())
			BaseCharacterMovement->bAllowPhysicsRotationDuringAnimRootMotion = true;
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UTPRotationAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (const auto Player = Cast<ATPBaseCharacter>(MeshComp->GetOwner()))
		if (const auto BaseCharacterMovement = Player->GetBaseCharacterMovement())
			BaseCharacterMovement->bAllowPhysicsRotationDuringAnimRootMotion = false;
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
