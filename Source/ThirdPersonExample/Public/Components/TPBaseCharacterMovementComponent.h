// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPBaseCharacterMovementComponent.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UTPBaseCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool IsSprinting() const { return bIsSprinting; }
	virtual float GetMaxSpeed() const override;
	float GetMovementDirection() const;

	void StartSprint();
	void StopSprint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Movement: Sprint", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float SprintSpeed = 600.0f;

private:
	bool bIsSprinting;
};
