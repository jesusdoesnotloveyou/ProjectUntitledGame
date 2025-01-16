// Project Untitled Game by JDNLY. All Rights Reserved.


#include "Pickups/PUBasePickup.h"
#include "Components/SphereComponent.h"
#include "Interfaces/CombatSystem/Attackable.h"
#include "Components/TPHealthComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPUBasePickup, All, All);

APUBasePickup::APUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionRadius = 50.0f;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	CollisionComponent->InitSphereRadius(SphereCollisionRadius);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetRootComponent(CollisionComponent);
}

void APUBasePickup::Destroyed()
{
	UE_LOG(LogPUBasePickup, Warning, TEXT("Some effect after pickup was taken!"));
	UGameplayStatics::PlaySoundAtLocation(this, SoundOnTaken, GetActorLocation(), OnTakenVolumeMultiplier, OnTakenPitchMultiplier);
}

void APUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);

	GenerateRotationYaw();
}

void APUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0, RotationYaw, 0.0));
}

void APUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		UE_LOG(LogPUBasePickup, Warning, TEXT("Pickup was taken!"));
		// Some logic for respawn maybe or smth else
		//PickupWasTaken();
		Destroy();
	}
}

bool APUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	if (PlayerPawn->Implements<UDamagable>()) return false;

	const auto HealthComponent = PlayerPawn->GetComponentByClass<UTPHealthComponent>();
	if (!HealthComponent) return false;

	return HealthComponent->TryToAddPotionPickup();
}

void APUBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}