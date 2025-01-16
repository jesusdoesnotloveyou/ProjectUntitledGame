// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Components/TPWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "TPEquipWeaponAnimNotify.h"
#include "TPSaveAttackAnimNotify.h"
#include "TPResetComboAnimNotify.h"
#include "TPRollEndedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPWeaponComponent, All, All);

UTPWeaponComponent::UTPWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsWeaponEquiped = false;
}

void UTPWeaponComponent::BeginPlay()
{	
	Super::BeginPlay();
	
	InitAnimations();
	SpawnWeapon();
	check(CurrentWeapon);

	if (RollLauchFloatCurve)
	{
		InitializeRollTimeline();
	}
}

void UTPWeaponComponent::InitializeRollTimeline()
{
	FOnTimelineFloat RollLaunchUpdate;
	RollLaunchUpdate.BindUFunction(this, FName("RollUpdate"));
	RollLaunchTimeline.AddInterpFloat(RollLauchFloatCurve, RollLaunchUpdate);
	RollLaunchTimeline.SetLooping(false);
}

void UTPWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RollLaunchTimeline.TickTimeline(DeltaTime);
}

void UTPWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentWeapon->Destroy();
	Super::EndPlay(EndPlayReason);
}

void UTPWeaponComponent::ReactToHit()
{
	UE_LOG(LogTPWeaponComponent, Error, TEXT("ReactToHit() called!"));

	if (HitAnimMontages.Num() != 0)
	{
		PlayAnimMontage(HitAnimMontages[FMath::RandHelper(HitAnimMontages.Num())]);
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetOwner()->GetActorLocation(), HitVolumeMultiplier);
}

void UTPWeaponComponent::Attack()
{
	if (!CanAttack()) return;

	UE_LOG(LogTPWeaponComponent, Warning, TEXT("Is Attacking before = %d"), bIsAttacking);
	UE_LOG(LogTPWeaponComponent, Warning, TEXT("AttackCount = %i"), AttackCount);

	if (bIsAttacking)
	{
		bSaveAttack = true;
	}
	else
	{
		bIsAttacking = true;
		PlayAttackMontageByIndex(AttackCount);
	}
	UE_LOG(LogTPWeaponComponent, Warning, TEXT("Is Attacking after = %d"), bIsAttacking);
}

// Methods are triggered by animNotifies in attack animMontages
// Метод можно будет наполнить логикой в будущем
// сейчас он просто сбрасывает значение saveAttack, которое устанавливается при легкой атаке
// но фактически код может быть закомментирован, и ничего не изменится
void UTPWeaponComponent::OnSaveAttack()
{
	if (bSaveAttack)
	{
		bSaveAttack = false;
	}
	bIsAttacking = false;
}

void UTPWeaponComponent::OnResetCombo()
{
	UE_LOG(LogTPWeaponComponent, Warning, TEXT("OnResetCombo() called!"));
	bIsAttacking = false;
	bSaveAttack = false;
	AttackCount = 0;
}

void UTPWeaponComponent::PlayAttackMontageByIndex(int32& AttackIndex)
{
	PlayAnimMontage(AttackAnimMontages[AttackIndex++], MeleeSpeed);
	AttackIndex = (AttackIndex) % AttackAnimMontages.Num();
}

void UTPWeaponComponent::OnResetState()
{
	OnResetCombo();
	OnRollEnd();
	bIsEquipAnimInProgress = false;
}

void UTPWeaponComponent::HeavyAttack()
{
	if (!CanAttack()) return;
	bIsAttacking = true;

	PlayAnimMontage(HeavyAttackAnimMontage, MeleeSpeed);
}

bool UTPWeaponComponent::CanAttack()
{
	if (!IsWeaponEquiped() || bIsRolling || bIsEquipAnimInProgress || bIsAttacking) return false;
	return true;
}

void UTPWeaponComponent::StartWeaponSwing(TSubclassOf<UDamageType> InDamageTypeClass)
{
	CurrentWeapon->StartSwinging(InDamageTypeClass);
}

void UTPWeaponComponent::StopWeaponSwing()
{
	CurrentWeapon->StopSwinging();
}

void UTPWeaponComponent::StartBlocking()
{
	if (!bIsWeaponEquiped || bIsEquipAnimInProgress || bIsRolling) return;
	bIsBlockRequested = true;
}

void UTPWeaponComponent::StopBlocking()
{
	bIsBlockRequested = false;
}

void UTPWeaponComponent::Roll()
{
	if (!bIsWeaponEquiped || bIsEquipAnimInProgress || bIsRolling) return;
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	// To discard block if we are rolling
	bIsBlockRequested = false;
	bIsRolling = true;

	// Very important
	Character->SetActorRotation(Character->GetLastMovementInputVector().ToOrientationRotator());
	PlayAnimMontage(RollAnimMontage, RollSpeed);
	RollLaunchTimeline.PlayFromStart();
}

void UTPWeaponComponent::RollUpdate(float Alpha)
{
	const auto ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		auto CurrentLocation = ComponentOwner->GetActorLocation();
		const auto NextTickLocation = ComponentOwner->GetActorForwardVector() * RollImpulse + CurrentLocation;

		CurrentLocation = FMath::Lerp(CurrentLocation, NextTickLocation, Alpha);
		ComponentOwner->SetActorLocation(CurrentLocation, true);
	}
}

// For Notifies in AnimMontages
void UTPWeaponComponent::InitAnimations()
{
	if (EquipAnimMontages.Num() == 0) return;
	// Might be good idea to move cicle iteration logic in separate
	for (const auto AnimMontage : EquipAnimMontages)
	{
		if (!AnimMontage) continue;
		const auto NotifyEvents = AnimMontage->Notifies;
		for (auto NotifyEvent : NotifyEvents) {
			if (const auto EquipNotify = Cast<UTPEquipWeaponAnimNotify>(NotifyEvent.Notify))
			{
				EquipNotify->OnWeaponEquipedNotified.AddUObject(this, &UTPWeaponComponent::OnEquipWeapon);
			}
		}
	}

	if (AttackAnimMontages.Num() == 0) return;
	for (const auto AnimMontage : AttackAnimMontages)
	{
		if (!AnimMontage) continue;
		const auto NotifyEvents = AnimMontage->Notifies;
		for (auto NotifyEvent : NotifyEvents) {
			if (const auto SaveAttackNotify = Cast<UTPSaveAttackAnimNotify>(NotifyEvent.Notify))
			{
				SaveAttackNotify->OnSaveAttackNotified.AddUObject(this, &UTPWeaponComponent::OnSaveAttack);
			}
			if (const auto ResetComboNotify = Cast<UTPResetComboAnimNotify>(NotifyEvent.Notify))
			{
				ResetComboNotify->OnResetComboNotified.AddUObject(this, &UTPWeaponComponent::OnResetCombo);
			}
		}
	}

	if (!HeavyAttackAnimMontage) return;
	{
		const auto NotifyEvents = HeavyAttackAnimMontage->Notifies;
		for (auto NotifyEvent : NotifyEvents) {
			if (const auto SaveAttackNotify = Cast<UTPSaveAttackAnimNotify>(NotifyEvent.Notify))
			{
				SaveAttackNotify->OnSaveAttackNotified.AddUObject(this, &UTPWeaponComponent::OnSaveAttack);
			}
			if (const auto ResetComboNotify = Cast<UTPResetComboAnimNotify>(NotifyEvent.Notify))
			{
				// Should use state to avoid this copying of logic for reset
				ResetComboNotify->OnResetComboNotified.AddUObject(this, &UTPWeaponComponent::OnResetCombo);
			}
		}
	}

	if (HitAnimMontages.Num() == 0) return;
	for (const auto AnimMontage : HitAnimMontages)
	{
		if (!AnimMontage) continue;
		const auto NotifyEvents = AnimMontage->Notifies;
		for (auto NotifyEvent : NotifyEvents) 
		{
			if (const auto ResetComboNotify = Cast<UTPResetComboAnimNotify>(NotifyEvent.Notify))
			{
				// Should use state to avoid this copying of logic for reset
				ResetComboNotify->OnResetComboNotified.AddUObject(this, &UTPWeaponComponent::OnResetState);
			}
		}
	}
	// Roll and Dash
	if (!RollAnimMontage) return;

	const auto NotifyEvents = RollAnimMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents) {
		if (const auto RollEndNotify = Cast<UTPRollEndedAnimNotify>(NotifyEvent.Notify))
		{
			RollEndNotify->OnRollEndNotified.AddUObject(this, &UTPWeaponComponent::OnResetState);
		}
	}
}

void UTPWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	auto Weapon = GetWorld()->SpawnActor<ATPBaseWeapon>(WeaponClass);
	if (!Weapon) return;

	Weapon->SetOwner(Character);
	//TODO: Weapons.Add(Weapon);
	AttachWeaponToSocket(Weapon, Character->GetMesh(), ArmorySocketName);
	CurrentWeapon = Weapon;
}

void UTPWeaponComponent::AttachWeaponToSocket(ATPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UTPWeaponComponent::PlayAnimMontage(UAnimMontage* Animation, float AnimationSpeed /*= 1.0f*/)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UTPWeaponComponent::OnEquipWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (bIsWeaponEquiped)
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), ArmorySocketName);
		bIsWeaponEquiped = false;
	}
	else
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmedSocketName);
		bIsWeaponEquiped = true;
	}

	bIsEquipAnimInProgress = false;
}

void UTPWeaponComponent::EquipWeapon()
{
	if (bIsEquipAnimInProgress || bIsAttacking || bIsBlockRequested || bIsRolling) return;

	bIsEquipAnimInProgress = true;
	if (bIsWeaponEquiped)
	{
		// Unequip montage
		PlayAnimMontage(EquipAnimMontages[1], EquippingSpeed);
	}
	else
	{
		// Equip montage
		PlayAnimMontage(EquipAnimMontages[0], EquippingSpeed);
	}
}

void UTPWeaponComponent::OnRollEnd()
{
	bIsRolling = false;
}

bool UTPWeaponComponent::IsEquipAnimInProgress() const
{
	return bIsEquipAnimInProgress;
}

bool UTPWeaponComponent::IsWeaponEquiped() const
{
	return (CurrentWeapon && bIsWeaponEquiped);
}

bool UTPWeaponComponent::IsBlockRequested() const
{ 
	return bIsBlockRequested; 
}

bool UTPWeaponComponent::IsRolling() const
{
	return bIsRolling;
}

void UTPWeaponComponent::SetTarget(bool bIsTargeted)
{
	bIsBeeingTargeted = bIsTargeted;
}

bool UTPWeaponComponent::IsBeeingTargeted() const
{
	return bIsBeeingTargeted;
}