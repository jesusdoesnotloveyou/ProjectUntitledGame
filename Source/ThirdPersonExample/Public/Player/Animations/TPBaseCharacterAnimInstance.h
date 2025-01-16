// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPBaseCharacterAnimInstance.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API UTPBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	FVector Velocity;

	// BlueprintReadWrite to compute direction for AI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Animation")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	bool bIsFalling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	bool bIsAccelerating = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	bool bIsCrouching = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	bool bIsBlockRequested = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	bool bIsArmed = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	bool bIsFocusing = false;

private:
	// The same field in Controller, but there is a soft object pointer
	TWeakObjectPtr<class ATPBaseCharacter> CachedBaseCharacter;
};
