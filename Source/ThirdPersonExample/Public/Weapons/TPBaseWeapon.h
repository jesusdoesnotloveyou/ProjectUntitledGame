// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPBaseWeapon.generated.h"

UCLASS()
class THIRDPERSONEXAMPLE_API ATPBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ATPBaseWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Components")
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Sockets")
	FName WeaponBladeStartSocketName = "blade_start";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Sockets")
	FName WeaponBladeEndSocketName = "blade_end";
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseWeaponDamage = 10.0f;

	// For Light and Heavy Attacks
	TSubclassOf<UDamageType> WeaponDamageTypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitStop")
	float HitStopDuration = 0.05f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitStop")
	float TimeDilationValue = 0.2f;
	
	virtual void BeginPlay() override;

public:	
	void StartSwinging(TSubclassOf<UDamageType> InDamageTypeClass);
	void StopSwinging();

	virtual void MakeHit();

	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess))
	float SphereCollisionRadius = 10.0f;

	FTimerHandle FHitStopTimerHandle;


	bool bIsWeaponCollisionEnabled = false;
	FCollisionShape WeaponBladeCollisionShape;
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess))
	TArray<AActor*> AlreadyHittedActors;

	void MakeDamage(const FHitResult& HitResult);
	AController* GetController() const;

	void StartHitStop();
	void EndHitStop();
};
