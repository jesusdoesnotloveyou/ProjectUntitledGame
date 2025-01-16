// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/TPDummyCharacter.h"
#include "PUBossCharacter.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API APUBossCharacter : public ATPDummyCharacter
{
	GENERATED_BODY()

public:
	APUBossCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnDeath() override;
};
