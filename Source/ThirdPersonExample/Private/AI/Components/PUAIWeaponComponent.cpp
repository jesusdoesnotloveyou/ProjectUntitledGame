// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/Components/PUAIWeaponComponent.h"
#include "GameFramework/Character.h"

void UPUAIWeaponComponent::Attack()
{
	PlayAnimMontage(AttackAnimMontages[0], MeleeSpeed);
}

void UPUAIWeaponComponent::HeavyAttack()
{

}

// Gotta implement AI in CPP to make this feature work

//void UPUAIWeaponComponent::EquipWeapon()
//{
//	Super::EquipWeapon();
//}

void UPUAIWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character && GetWorld())
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmedSocketName);
	}
}