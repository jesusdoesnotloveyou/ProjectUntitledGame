// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PUCoreTypes.h"
#include "TPGameModeBase.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API ATPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATPGameModeBase();

	FOnGameStateChangedSignature OnGameStateChanged;

	virtual void StartPlay() override;
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
	virtual bool ClearPause() override;
private:
	EPUGameState GameState = EPUGameState::WaitingToStart;

	void SetGameState(EPUGameState);
	UFUNCTION()
	void GameOver();
};
