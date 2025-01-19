// Project Untitled Game by JDNLY. All Rights Reserved.

#include "AI/PUAICharacter.h"
#include "AI/TPBaseAIController.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TPHealthComponent.h"
#include "AI/Components/TPAIWeaponComponent.h"
#include "UI/TPHealthBarWidget.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPDummyCharacter, All, All);

APUAICharacter::APUAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UTPAIWeaponComponent>("WeaponComponent"))
{
	PrimaryActorTick.bCanEverTick = true;
	// Pawn interface for AI
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ATPBaseAIController::StaticClass();
	
	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
		GetCharacterMovement()->MaxWalkSpeed = 250.0f;
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
	
	LockOnWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("LockOnWidgetComponent");
	LockOnWidgetComponent->SetupAttachment(GetRootComponent());
	LockOnWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	LockOnWidgetComponent->SetDrawSize(FVector2D(15.0));
}

void APUAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthWidgetComponent);
	check(LockOnWidgetComponent);
}

void APUAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);
	
	const auto HealthBarWidget = Cast<UTPHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget) return;

	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent(), Health, HealthDelta);
}

void APUAICharacter::OnDeath()
{
	Super::OnDeath();

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	const auto EnemyController = Cast<AAIController>(Controller);

	if (EnemyController && EnemyController->BrainComponent)
	{
		EnemyController->BrainComponent->Cleanup();
	}

	// Check my thoughts about Targeting below
	WeaponComponent->SetTarget(false);
}

void APUAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHealthBarVisibility();
	UpdateTargetVisibility();
}

void APUAICharacter::UpdateHealthBarVisibility()
{
	if (!GetWorld() ||
		!GetWorld()->GetFirstPlayerController() ||
		!GetWorld()->GetFirstPlayerController()->GetPawn())
		return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	const auto Distance = FVector::Distance(GetActorLocation(), PlayerLocation);

	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance && HealthComponent && !HealthComponent->IsDead(), true);
}

// Targeting should be rewrited different way without setting bIsBeeingTargeted in WeaponComponent from PlayerCharacter
// I have to finish project before DD so I've implemented feature like this. But only for now.
void APUAICharacter::UpdateTargetVisibility()
{
	if (!GetWorld() || !WeaponComponent) return;
	LockOnWidgetComponent->SetVisibility(WeaponComponent->IsBeeingTargeted(), true);
}