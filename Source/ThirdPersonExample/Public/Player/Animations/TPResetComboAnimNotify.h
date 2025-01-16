// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TPResetComboAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnResetComboNotifiedSignature);

UCLASS()
class THIRDPERSONEXAMPLE_API UTPResetComboAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	FOnResetComboNotifiedSignature OnResetComboNotified;
};
