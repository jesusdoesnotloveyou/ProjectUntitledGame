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
	virtual void OnDeath();
	virtual void BeginPlay() override;

	// Movement interface
	UTPBaseCharacterMovementComponent* BaseCharacterMovement;
	// Health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTPHealthComponent* HealthComponent;
	// Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTPWeaponComponent* WeaponComponent;

#pragma region Death
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	class UAnimMontage* DeathAnimMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float LifeSpanOnDeath = 5.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	USoundBase* SoundOnDeath;
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float DeathPitchMultiplier = 1.f;
	UPROPERTY(EditDefaultsOnly, Category = "Death")
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
