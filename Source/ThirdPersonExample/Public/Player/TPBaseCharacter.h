// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/TPAttributeSet.h"
#include "AbilitySystem/TPAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "TPBaseCharacter.generated.h"

// fwd declarations
class UTPBaseCharacterMovementComponent;
class UTPHealthComponent;
class UTPWeaponComponent;
class USoundBase;

UCLASS(config = Game)
class ATPBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ATPBaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;
	// For sprint logic
	virtual void Tick(float DeltaSeconds) override;

	/** Returns Custom CharacterMovement subobject **/
	FORCEINLINE UTPBaseCharacterMovementComponent* GetBaseCharacterMovement() { return BaseCharacterMovement; }

protected:
	virtual void OnHealthChanged(float Health, float HealthDelta);
	virtual void OnHitReact();
	virtual void OnDeath();
	virtual void InitAnimations();

	virtual void BeginPlay() override;

	// Movement interface
	UTPBaseCharacterMovementComponent* BaseCharacterMovement;
	// Health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTPHealthComponent* HealthComponent;
	// Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTPWeaponComponent* WeaponComponent;

#pragma region Animations
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit | Animation")
	TArray<UAnimMontage*> HitAnimMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Death | Animation")
	class UAnimMontage* DeathAnimMontage;
#pragma endregion
	UPROPERTY(EditDefaultsOnly, Category = "Death | Animation")
	float LifeSpanOnDeath = 5.0f;
	
#pragma region Sounds
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit | Sound")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit | Sound")
	float HitVolumeMultiplier = 0.6f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Death | Sound")
	USoundBase* SoundOnDeath;

	UPROPERTY(EditDefaultsOnly, Category = "Death | Sound")
	float DeathPitchMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Death | Sound")
	float DeathVolumeMultiplier = 1.f;
#pragma endregion

	
public:
	bool IsEquipAnimInProgress() const;
	bool IsBlockRequested() const;
	bool IsWeaponEquiped() const;
	bool IsRolling() const;

	/** GAS **/
	// Attributes
	UPROPERTY()
	float GASHealth;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*UFUNCTION()
	void OnHealthChangedInternal(const FOnAttributeChangeData& Data);*/
protected:
	UPROPERTY()
	const UTPAttributeSet* AttributeSet;

	UPROPERTY(/*Category = "Components"*/)
	UTPAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	FGameplayTag SprintAbilityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	FGameplayTag CrouchAbilityTag;

	// TO DO
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	FGameplayTag EquipWeaponAbilityTag;

	bool bAreAbilitiesAdded;

private:
	void InitGameplayAbilitySystem(AController* NewController);
};