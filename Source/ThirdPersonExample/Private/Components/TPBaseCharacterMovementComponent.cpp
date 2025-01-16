// Project Untitled Game by JDNLY. All Rights Reserved.


#include "Components/TPBaseCharacterMovementComponent.h"

float UTPBaseCharacterMovementComponent::GetMaxSpeed() const
{
    float Result = Super::GetMaxSpeed();

    if (bIsSprinting)
    {
        Result = SprintSpeed;
    }
    return Result;
}

float UTPBaseCharacterMovementComponent::GetMovementDirection() const
{
    if (GetOwner()->GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetOwner()->GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetOwner()->GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetOwner()->GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void UTPBaseCharacterMovementComponent::StartSprint()
{
    bIsSprinting = true;
    // For console contollers
    //bForceMaxAccel = 1;
}

void UTPBaseCharacterMovementComponent::StopSprint()
{
    bIsSprinting = false;
    // For console contollers
    //bForceMaxAccel = 0;
}