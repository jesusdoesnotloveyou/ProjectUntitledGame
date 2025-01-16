// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "TPDamageTypeBase.generated.h"

UENUM()
enum class ETPDamageType : uint8 
{
	None = 0,
	Left,
	Right,
	Front,
	Back,
	MAX = 5
};

UCLASS()
class THIRDPERSONEXAMPLE_API UTPDamageTypeBase : public UDamageType
{
	GENERATED_BODY()
public:
	UTPDamageTypeBase();

	ETPDamageType DamageType;

	float Damage = 10.0f;
	
};

UCLASS()
class THIRDPERSONEXAMPLE_API UTPDamageTypeHeavy : public UTPDamageTypeBase
{
	GENERATED_BODY()
public:
	UTPDamageTypeHeavy();
};

UCLASS()
class THIRDPERSONEXAMPLE_API UTPDamageTypeLeft : public UTPDamageTypeBase
{
	GENERATED_BODY()
public:	
	UTPDamageTypeLeft();
};

UCLASS()
class THIRDPERSONEXAMPLE_API UTPDamageTypeRight : public UTPDamageTypeBase
{
	GENERATED_BODY()
public:
	UTPDamageTypeRight();
};

UCLASS()
class THIRDPERSONEXAMPLE_API UTPDamageTypeBack : public UTPDamageTypeBase
{
	GENERATED_BODY()
public:
	UTPDamageTypeBack();
};

UCLASS()
class THIRDPERSONEXAMPLE_API UTPDamageTypeFront : public UTPDamageTypeBase
{
	GENERATED_BODY()
public:
	UTPDamageTypeFront();
};