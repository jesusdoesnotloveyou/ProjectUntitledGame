// Project Untitled Game by JDNLY. All Rights Reserved.

#include "TPBaseCharacter.h"
#include "Components/TPBaseCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TPHealthComponent.h"
#include "Components/TPWeaponComponent.h"
#include "AbilitySystem/TPAbilitySystemComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPBaseCharacter, All, All);

//////////////////////////////////////////////////////////////////////////
// ATPBaseCharacter

ATPBaseCharacter::ATPBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UTPBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	PrimaryActorTick.bCanEverTick = true;
	
	BaseCharacterMovement = StaticCast<UTPBaseCharacterMovementComponent*>(GetCharacterMovement());

	HealthComponent = CreateDefaultSubobject<UTPHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UTPWeaponComponent>("WeaponComponent");

	AbilitySystemComponent = CreateDefaultSubobject<UTPAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UTPAttributeSet>("AttributeSet");

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATPBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitGameplayAbilitySystem(NewController);
}

void ATPBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GetBaseCharacterMovement());
	check(GetCapsuleComponent());
	check(GetMesh());
	check(HealthComponent);
	check(WeaponComponent);

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATPBaseCharacter::OnHealthChanged);
	HealthComponent->OnDeath.AddUObject(this, &ATPBaseCharacter::OnDeath);

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (ASC) {
		AttributeSet = ASC->GetSet<UTPAttributeSet>();
	}
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ATPBaseCharacter::OnHealthChangedInternal);
}

void ATPBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	if (FMath::IsNearlyZero(HealthDelta) || FMath::IsNearlyEqual(Health, HealthDelta)) return;

	if (HealthDelta < 0)
	{
		WeaponComponent->ReactToHit();
	}
}

void ATPBaseCharacter::OnDeath()
{
	UE_LOG(LogTPBaseCharacter, Display, TEXT("Character %s is dead"), *GetName());
	BaseCharacterMovement->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	UGameplayStatics::PlaySoundAtLocation(this, SoundOnDeath, GetActorLocation(), DeathVolumeMultiplier, DeathPitchMultiplier);
}

//////////////////////////////////////////////////////////////////////////
// GAS

UAbilitySystemComponent* ATPBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

/*
void ATPBaseCharacter::OnHealthChangedInternal(const FOnAttributeChangeData& Data)
{
	Health = AttributeSet->GetHealth();
}*/

// Weapon Component
bool ATPBaseCharacter::IsEquipAnimInProgress() const
{
	return WeaponComponent->IsEquipAnimInProgress();
}

bool ATPBaseCharacter::IsWeaponEquiped() const
{
	return WeaponComponent->IsWeaponEquiped();
}

bool ATPBaseCharacter::IsRolling() const
{
	return WeaponComponent->IsRolling();
}

bool ATPBaseCharacter::IsBlockRequested() const
{
	return WeaponComponent->IsBlockRequested();
}

void ATPBaseCharacter::InitGameplayAbilitySystem(AController* NewController)
{
	AbilitySystemComponent->InitAbilityActorInfo(NewController, this);
	if (!bAreAbilitiesAdded)
	{
		for (TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass));

		}
		bAreAbilitiesAdded = true;
	}
}