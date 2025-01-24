// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "Weapons/TPBaseWeapon.h"
#include "TPWeaponComponent.generated.h"

class ATPBaseWeapon;

class UCameraShakeBase;
class UCameraComponent;
class UCurveFloat;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONEXAMPLE_API UTPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTPWeaponComponent();

	// Combat System
	virtual void Attack();
	virtual void HeavyAttack();
	bool CanAttack();

	void StartWeaponSwing(TSubclassOf<UDamageType> InDamageTypeClass);
	void StopWeaponSwing();

	void StartBlocking();
	void StopBlocking();
	FOnBlockedSignature OnBlocked;

	virtual void EquipWeapon();
	
	void Roll();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	ATPBaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

protected:
#pragma region Animations
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation | Equip")
	TArray<UAnimMontage*> EquipAnimMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation | Equip"/*, ClampMin = ("1.0")*/)
	float EquippingSpeed = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation | Attack")
	TArray<UAnimMontage*> AttackAnimMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation | Attack")
	UAnimMontage* HeavyAttackAnimMontage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation | Attack"/*, ClampMin = ("1.0")*/)
	float MeleeSpeed = 1.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation | Dodge")
	UAnimMontage* RollAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation | Dodge"/*, ClampMin = ("1.0")*/)
	float RollSpeed = 1.5f;
#pragma endregion

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmedSocketName = "weapon_socket";
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName ArmorySocketName = "armory_socket";

	UPROPERTY()
	class ATPBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ATPBaseWeapon> WeaponClass;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "AI | Weapon")
	bool IsWeaponEquiped() const;

	bool IsEquipAnimInProgress() const;
	bool IsBlockRequested() const;
	bool IsRolling() const;

	// Combat System for animNotifies
	void OnResetState();
	// Light attack strike
	int32 AttackCount = 0;
	// Maybe usefull for BP
	UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking = false;
	bool bSaveAttack = false;
	// Roll and dash
	bool bIsRolling = false;

	bool bIsEquipAnimInProgress = false;
	bool bIsWeaponEquiped = false;
	bool bIsBlockRequested = false;
private:
	FTimeline RollLaunchTimeline;
	void InitializeRollTimeline();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation | Dodge", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* RollLauchFloatCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation | Dodge", meta = (AllowPrivateAccess = "true"))
	float RollImpulse = 10.0f;

	UFUNCTION()
	void RollUpdate(float Alpha);

	// Combat System
	//~ For animNotifies
	void OnSaveAttack();
	void OnResetCombo();
	// ~
	void PlayAttackMontageByIndex(int32& AttackIndex);
	
	void SpawnWeapon();
	void InitAnimations();
	// Callback for AnimNotifies
	void OnEquipWeapon();
	void OnRollEnd();

protected:
	void PlayAnimMontage(UAnimMontage* Animation, float AnimationSpeed = 1.0f);	
	void AttachWeaponToSocket(ATPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

public:
	// BAD. Only for AI
	virtual void SetTarget(bool bIsTargeted);
	virtual bool IsBeeingTargeted() const;
private:
	bool bIsBeeingTargeted = false;
	//
};