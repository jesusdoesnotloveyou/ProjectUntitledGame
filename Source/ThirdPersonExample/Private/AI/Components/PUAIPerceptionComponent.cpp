// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/Components/PUAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/TPHealthComponent.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPAIPerceptionComponent, All, All);

UPUAIPerceptionComponent::UPUAIPerceptionComponent()
{

}

AActor* UPUAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercievedActors;

    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);
    if (PercievedActors.Num() == 0)
    {   
        UE_LOG(LogTPAIPerceptionComponent, Warning, TEXT("PercievedActors.Num() = 0"));
        return nullptr;
    }
    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) {
        UE_LOG(LogTPAIPerceptionComponent, Warning, TEXT("!Controller"));
        return nullptr;
    }
    
    const auto ControlledPawn = Controller->GetPawn();
    if (!ControlledPawn) {
        UE_LOG(LogTPAIPerceptionComponent, Warning, TEXT("!ControlledPawn"));
        return nullptr;
    }

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for (const auto PercievedActor : PercievedActors)
    {
        const auto HealthComponent = PercievedActor->GetComponentByClass<UTPHealthComponent>();
        if (HealthComponent && !HealthComponent->IsDead())
        {
            const auto CurrentDistance = (PercievedActor->GetActorLocation() - ControlledPawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercievedActor;
            }
        }
    }

    if (!BestPawn)
    {
        UE_LOG(LogTPAIPerceptionComponent, Warning, TEXT("Best pawn isn't valid"));
    }

    return BestPawn;
}