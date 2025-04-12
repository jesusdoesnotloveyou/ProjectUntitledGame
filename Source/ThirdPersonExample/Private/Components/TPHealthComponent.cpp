// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Components/TPHealthComponent.h"
#include "Dev/DamageTypes/TPDamageTypeBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPHealthComponent, All, All);

UTPHealthComponent::UTPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTPHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

float UTPHealthComponent::GetHealth() const
{
	return Health;
}

bool UTPHealthComponent::IsDead() const
{
	return FMath::IsNearlyZero(Health);
}

bool UTPHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UTPHealthComponent::UseHealPotion()
{
	if (IsDead() || PotionsAmount == 0) return;

	bIsHealing = true;
	OnGameplayStateChanged.Broadcast(EPUGameplayState::Healing);
	PlayAnimMontage(HealAnimMontage);

	const auto HealBuf = Potion.HealEffect * Potion.HealModifier;
	SetHealth(Health + HealBuf);
	--PotionsAmount;
	UE_LOG(LogTPHealthComponent, Error, TEXT("Heal Buf: %f"), HealBuf);
}

void UTPHealthComponent::PlayAnimMontage(UAnimMontage* Animation, float AnimationSpeed /*= 1.0f*/)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	Character->PlayAnimMontage(Animation);
}

bool UTPHealthComponent::TryToAddPotionPickup()
{
	// To prevent taking potion when player is dead
	if (IsDead()) return false;
	++PotionsAmount;
	UE_LOG(LogTPHealthComponent, Warning, TEXT("Potions: %i"), PotionsAmount);
	return true;
}

int32 UTPHealthComponent::GetNumberOfPotions() const
{
	return PotionsAmount;
}

void UTPHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &UTPHealthComponent::OnTakePointDamage);
	}
}

void UTPHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTPHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy,
										   FVector HitLocation, class UPrimitiveComponent* FHitComponent,
										   FName BoneName, FVector ShotFromDirection,
										   const class UDamageType* DamageType, AActor* DamageCauser)
{
	//UE_LOG(LogTPHealthComponent, Warning, TEXT("Bone name: %s"), *BoneName.ToString());
	const auto WeaponDamageType = Cast<UTPDamageTypeHeavy>(DamageType);
	if (WeaponDamageType)
	{
		Damage = Damage * 3.0f;
	}
	const auto FinalDamage = Damage * GetDamageModifier();
	//UE_LOG(LogTPHealthComponent, Warning, TEXT("OnTakePointDamage() called: %f, bone: %s"), Damage, *BoneName.ToString());
	
	ApplyDamage(FinalDamage, InstigatedBy, DamageType);
}
// InstigatedBy for AI to know who is attacking it
void UTPHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy, const UDamageType* DamageType)
{
	if (Damage <= 0 || IsDead()) return;

	SetHealth(Health - Damage);
	if (IsDead()) {
		OnDeath.Broadcast();
	}

	PlayCameraShake();
	ReportDamageEvent(Damage, InstigatedBy);
}

// 
void UTPHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	const auto Controller = Pawn->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(DamageCameraShake);
	//UE_LOG(LogTPHealthComponent, Error, TEXT("Camera shake is playing"));
}

float UTPHealthComponent::GetDamageModifier()
{
	return 1.0f;
}

void UTPHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner())
		return;
	UAISense_Damage::ReportDamageEvent(GetWorld(),                                  //
	                                   GetOwner(),                                  //
	                                   InstigatedBy->GetPawn(),                     //
	                                   Damage,                                      //
	                                   InstigatedBy->GetPawn()->GetActorLocation(), //
	                                   GetOwner()->GetActorLocation());
}