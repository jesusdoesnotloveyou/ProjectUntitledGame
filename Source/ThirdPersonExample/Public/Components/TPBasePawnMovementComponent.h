// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TPBasePawnMovementComponent.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UTPBasePawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void JumpStart();

protected:
	UPROPERTY(EditAnywhere, Category=Movement)
	float MaxSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	bool bEnableGravity;
	
	UPROPERTY(EditAnywhere, Category = Movement)
	float InitialJumpVelocity = 500.0f;

public:		
	virtual float GetMaxSpeed() const override;

private: 
	FVector VerticalVelocity = FVector::ZeroVector;
	bool bIsFalling = false;
};
