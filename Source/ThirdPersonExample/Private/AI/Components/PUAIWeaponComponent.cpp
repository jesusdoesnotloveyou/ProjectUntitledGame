// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/Components/PUAIWeaponComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "BrainComponent.h"

void UPUAIWeaponComponent::Attack()
{
	//if (!CanAttack()) return;
	PlayAnimMontage(AttackAnimMontages[0], MeleeSpeed);
}

void UPUAIWeaponComponent::HeavyAttack()
{
	PlayAnimMontage(HeavyAttackAnimMontage, MeleeSpeed);
}

// Gotta implement AI in CPP to make this feature work

void UPUAIWeaponComponent::EquipWeapon()
{
	bIsEquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontages[0], EquippingSpeed);
}

void UPUAIWeaponComponent::UnequipWeapon()
{
	bIsEquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontages[1], EquippingSpeed);
}

bool UPUAIWeaponComponent::IsMontagesPlaying(const TArray<UAnimMontage*>& AnimMontages) const
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character || !Character->GetMesh()) return false;

	const auto AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (!AnimInstance) return false;

	for (const auto Montage : AnimMontages)
	{
		if (AnimInstance->Montage_IsPlaying(Montage)) return true;
	}
	return false;
}

bool UPUAIWeaponComponent::IsAttackMontagesPlaying() const
{
	return IsMontagesPlaying(AttackAnimMontages);
}

void UPUAIWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	/*ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character && GetWorld())
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmedSocketName);
	}*/
}