// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/PUBossCharacter.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "AI/Components/TPAIWeaponComponent.h"

APUBossCharacter::APUBossCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void APUBossCharacter::OnDeath()
{
	SetLifeSpan(LifeSpanOnDeath);
	PlayAnimMontage(DeathAnimMontage);

	const auto EnemyController = Cast<AAIController>(Controller);

	if (EnemyController && EnemyController->BrainComponent)
	{
		EnemyController->BrainComponent->Cleanup();
	}

	// Check my thoughts about Targeting below
	WeaponComponent->SetTarget(false);
}