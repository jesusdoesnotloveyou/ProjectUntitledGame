// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TPRollEndedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRollEndNotifiedSignature)

UCLASS()
class THIRDPERSONEXAMPLE_API UTPRollEndedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FOnRollEndNotifiedSignature OnRollEndNotified;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
