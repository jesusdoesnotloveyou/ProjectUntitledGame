// Project Untitled Game by JDNLY. All Rights Reserved.

#include "TPDummyCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TPHealthComponent.h"
#include "Components/TPAIWeaponComponent.h"
#include "UI/TPHealthBarWidget.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPDummyCharacter, All, All);

ATPDummyCharacter::ATPDummyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UTPAIWeaponComponent>("WeaponComponent"))
{
	PrimaryActorTick.bCanEverTick = true;
	
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

void ATPDummyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthWidgetComponent);
	check(LockOnWidgetComponent);
}

void ATPDummyCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);
	
	const auto HealthBarWidget = Cast<UTPHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget) return;

	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent(), Health, HealthDelta);
}

void ATPDummyCharacter::OnDeath()
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

void ATPDummyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHealthBarVisibility();
	UpdateTargetVisibility();
}

void ATPDummyCharacter::UpdateHealthBarVisibility()
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
void ATPDummyCharacter::UpdateTargetVisibility()
{
	if (!GetWorld() || !WeaponComponent) return;
	LockOnWidgetComponent->SetVisibility(WeaponComponent->IsBeeingTargeted(), true);
}