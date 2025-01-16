// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PUBasePickup.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPickupTakenSignature);

class USoundBase;
class USphereComponent;

UCLASS()
class THIRDPERSONEXAMPLE_API APUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:
	FOnPickupTakenSignature OnPickupTaken;

	APUBasePickup();
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	USphereComponent* CollisionComponent;

#pragma region Sound
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float OnTakenPitchMultiplier = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float OnTakenVolumeMultiplier = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* SoundOnTaken;
#pragma endregion

	// virtual for future different pickup object types
	virtual bool GivePickupTo(APawn* PlayerPawn);
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void Destroyed() override;
private:
	float RotationYaw = 0.0f;
	void GenerateRotationYaw();
	float SphereCollisionRadius;
};
