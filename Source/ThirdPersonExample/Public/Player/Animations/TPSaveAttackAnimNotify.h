// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TPSaveAttackAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSaveAttackNotifiedSignature);

UCLASS()
class THIRDPERSONEXAMPLE_API UTPSaveAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	FOnSaveAttackNotifiedSignature OnSaveAttackNotified;
};
