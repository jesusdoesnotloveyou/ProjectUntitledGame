// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PUCoreTypes.h"
#include "PUPlayerController.generated.h"

class UInputAction;
//class UPURespawnComponent;

UCLASS()
class THIRDPERSONEXAMPLE_API APUPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseGameAction;

public:
	APUPlayerController();

protected:
	//UPURespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	void OnPauseGame();
	void OnGameStateChanged(EPUGameState NewGameState);
};
