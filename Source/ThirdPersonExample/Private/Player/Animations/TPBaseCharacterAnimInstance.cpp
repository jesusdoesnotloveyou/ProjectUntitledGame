// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/Animations/TPBaseCharacterAnimInstance.h"
#include "Player/TPBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TPBaseCharacterMovementComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

void UTPBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CachedBaseCharacter.IsValid()) return;
	
	UTPBaseCharacterMovementComponent* BaseCharacterMovement = CachedBaseCharacter->GetBaseCharacterMovement();
	if (!BaseCharacterMovement) return;
	
	bIsArmed = CachedBaseCharacter.Get()->IsWeaponEquiped();
	bIsBlockRequested = CachedBaseCharacter.Get()->IsBlockRequested();

	Velocity = BaseCharacterMovement->Velocity;

	Speed = BaseCharacterMovement->Velocity.Length();

	Direction = BaseCharacterMovement->GetMovementDirection();
	// Could make the same for IsFlying, IsSwimming and so on
	bIsFalling = BaseCharacterMovement->IsFalling();

	bIsAccelerating = BaseCharacterMovement->GetCurrentAcceleration().Length() > 0;

	bIsCrouching = BaseCharacterMovement->IsCrouching();

	bIsSprinting = BaseCharacterMovement->IsSprinting();

	// AI
	if (const auto AIController = Cast<AAIController>(CachedBaseCharacter->GetController()))
		bIsFocusing = AIController->GetFocusActor() ? true : false;
}

void UTPBaseCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(TryGetPawnOwner()->IsA<ATPBaseCharacter>(), TEXT("UTPBaseCharacterAnimInstance could only be used on ATPBaseCharacter"));
	CachedBaseCharacter = StaticCast<ATPBaseCharacter*>(TryGetPawnOwner());
}