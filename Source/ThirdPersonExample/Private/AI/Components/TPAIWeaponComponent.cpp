// Project Untitled Game by JDNLY. All Rights Reserved.


#include "AI/Components/TPAIWeaponComponent.h"
#include "GameFramework/Character.h"

void UTPAIWeaponComponent::Attack()
{
	PlayAnimMontage(AttackAnimMontages[0], MeleeSpeed);
}

void UTPAIWeaponComponent::HeavyAttack()
{

}

// Gotta implement AI in CPP to make this feature work

//void UTPAIWeaponComponent::EquipWeapon()
//{
//	Super::EquipWeapon();
//}

void UTPAIWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character && GetWorld())
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmedSocketName);
	}
}
