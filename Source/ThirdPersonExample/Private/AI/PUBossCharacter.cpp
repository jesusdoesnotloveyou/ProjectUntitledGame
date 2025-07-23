// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/PUBossCharacter.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "AI/Components/PUAIWeaponComponent.h"

APUBossCharacter::APUBossCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void APUBossCharacter::OnDeath()
{
	Super::OnDeath();
	PlayAnimMontage(DeathAnimMontage);
}