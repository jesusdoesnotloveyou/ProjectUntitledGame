// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PUCoreTypes.h"
#include "TPHealthComponent.generated.h"

class UCameraShakeBase;

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

USTRUCT(BlueprintType)
struct FHealPotion
{
	GENERATED_BODY()

public:
	FTimerHandle HealPotionTimer;
	float HealEffect = 30.0f;
	float HealModifier = 1.0f;
	float HealTime = 3.0f;
	// VFX for this type of potion
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONEXAMPLE_API UTPHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTPHealthComponent();

	FOnHealthChangedSignature OnHealthChanged;
	FOnDeathSignature OnDeath;
	FOnGameplayStateChangedSignature OnGameplayStateChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

	void SetHealth(float NewHealth);
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const;
	bool IsHealthFull() const;

	void UseHealPotion();
	FORCEINLINE bool IsHealing() const { return bIsHealing; }
	bool TryToAddPotionPickup();
	int32 GetNumberOfPotions() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* HealAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> DamageCameraShake;

	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	void PlayCameraShake();
	void PlayAnimMontage(UAnimMontage* Animation, float AnimationSpeed = 1.0f);

	float GetDamageModifier();
	void ApplyDamage(float Damage, AController* DamagedActor, const UDamageType* DamageType);
	void ReportDamageEvent(float Damage, AController* InstigatedBy);

	float Health = 0.0f;
	bool bIsHealing = false;
	int32 PotionsAmount = 0;
	FHealPotion Potion;
};