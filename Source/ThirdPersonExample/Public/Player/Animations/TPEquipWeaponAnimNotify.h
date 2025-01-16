// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TPEquipWeaponAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWeaponEquipedNotifiedSignature);

UCLASS()
class THIRDPERSONEXAMPLE_API UTPEquipWeaponAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FOnWeaponEquipedNotifiedSignature OnWeaponEquipedNotified;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
