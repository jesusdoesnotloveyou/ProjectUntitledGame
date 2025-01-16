// Project Untitled Game by JDNLY. All Rights Reserved.


#include "Components/TPBasePawnMovementComponent.h"
#include <Player/TPBasePawn.h>

void UTPBasePawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime)) return;

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PendingInput = GetPendingInputVector().GetClampedToMaxSize(1.0f);
	Velocity = PendingInput * MaxSpeed;
	ConsumeInputVector();

	if (bEnableGravity) {
		FHitResult OutHit;
		FVector Start = GetActorLocation();

		const auto Pawn = Cast<ATPBasePawn>(PawnOwner);
		float LineTraceLength = Pawn ? Pawn->GetCollisionSphereRadius() : 50.0f;

		FVector End = Start + FVector::DownVector * LineTraceLength;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());

		bool bWasFalling = bIsFalling;
		bIsFalling = !GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params);
		if (bIsFalling)
		{
			VerticalVelocity += GetGravityZ() * FVector::UpVector * DeltaTime;
			Velocity += VerticalVelocity;
		}
		else if (bWasFalling)
		{
			VerticalVelocity = FVector::ZeroVector;
		}
	}

	FVector Delta = Velocity * DeltaTime;
	if (!Delta.IsNearlyZero(1e-6f))
	{
		FQuat Rotation = UpdatedComponent->GetComponentQuat();
		FHitResult Hit(1.f);
		SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			HandleImpact(Hit, DeltaTime, Delta);
			// Try to slide the remaining distance along the surface.
			SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
		}
	}

	UpdateComponentVelocity();
}

void UTPBasePawnMovementComponent::JumpStart()
{
	VerticalVelocity = InitialJumpVelocity * FVector::UpVector;
}

float UTPBasePawnMovementComponent::GetMaxSpeed() const
{
	return MaxSpeed;
}
