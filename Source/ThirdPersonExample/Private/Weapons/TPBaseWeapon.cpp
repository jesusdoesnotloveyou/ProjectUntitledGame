// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Weapons/TPBaseWeapon.h"
#include "Engine/DamageEvents.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/CombatSystem/Attackable.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPBaseWeapon, All, All);

ATPBaseWeapon::ATPBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	WeaponBladeCollisionShape = FCollisionShape::MakeSphere(SphereCollisionRadius);
}

void ATPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

void ATPBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsWeaponCollisionEnabled)
	{
		MakeHit();
	}
}

void ATPBaseWeapon::StartSwinging(TSubclassOf<UDamageType> InDamageTypeClass)
{
	WeaponDamageTypeClass = InDamageTypeClass;
	bIsWeaponCollisionEnabled = true;
	AlreadyHittedActors.Empty();
}

void ATPBaseWeapon::StopSwinging()
{
	bIsWeaponCollisionEnabled = false;
	// ?
	EndHitStop();
	AlreadyHittedActors.Empty();
}

void ATPBaseWeapon::MakeHit()
{
	if (!GetWorld()) return;

	TArray<FHitResult> OutHitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;
	
	if (!GetWorld()->SweepMultiByChannel(OutHitResults,
		WeaponMesh->GetSocketLocation(WeaponBladeStartSocketName),
		WeaponMesh->GetSocketLocation(WeaponBladeEndSocketName),
		FQuat(),
		ECollisionChannel::ECC_Pawn, WeaponBladeCollisionShape,
		CollisionParams/*, FCollisionResponseParams*/)) return;

	for (auto& HitResult : OutHitResults)
	{
		MakeDamage(HitResult);
	}
}

void ATPBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();

	if (!DamagedActor ||
		AlreadyHittedActors.Contains(DamagedActor) ||
		GetOwner()->Implements<UDamagable>() == DamagedActor->Implements<UDamagable>())
		return;

	AlreadyHittedActors.AddUnique(DamagedActor);

	// Hit Stop Logic
	StartHitStop();
	
	FPointDamageEvent PointDamageEvent;
	PointDamageEvent.HitInfo = HitResult;
	PointDamageEvent.DamageTypeClass = WeaponDamageTypeClass;
	
	DamagedActor->TakeDamage(BaseWeaponDamage, PointDamageEvent, GetController(), this);
}

AController* ATPBaseWeapon::GetController() const {
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

// Also Hit Stop might be implemented as Global Time Dilation
//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilationValue);
// TODO: BUT the best way to implement this IS freezing the current animation as well as VFX, sounds etc.
// It should be performed through calling character mesh that usually responsible for animation playing
void ATPBaseWeapon::StartHitStop()
{
	if (GetOwner())
	{
		GetOwner()->CustomTimeDilation = TimeDilationValue;
	}
	for (const auto HittedActor : AlreadyHittedActors)
	{
		if (!HittedActor || HittedActor->CustomTimeDilation == TimeDilationValue) continue;
		HittedActor->CustomTimeDilation = TimeDilationValue;
	}
	GetWorldTimerManager().SetTimer(FHitStopTimerHandle, this, &ATPBaseWeapon::EndHitStop, HitStopDuration);
}

void ATPBaseWeapon::EndHitStop()
{
	if (GetOwner())
	{
		GetOwner()->CustomTimeDilation = 1.0f;
	}
	for (const auto HittedActor : AlreadyHittedActors)
	{
		if (!HittedActor || HittedActor->CustomTimeDilation == 1.0f) continue;
		HittedActor->CustomTimeDilation = 1.0f;
	}
	if (FHitStopTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FHitStopTimerHandle);
	}
}