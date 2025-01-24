#pragma once
#include "PUCoreTypes.generated.h"

// GameMode
// Changing levels
UENUM(BlueprintType)
enum class EPUGameState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	GameOver
};

UENUM(BlueprintType)
enum class EPUSoftWidgetType : uint8
{
	None = 0,
	Options,
	Credits,
	MAX = 3
};

// For Soft Widgets (strange logic, probably should rewrite it different way)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenSoftWidgetSignature, EPUSoftWidgetType);

// For GameMode
DECLARE_MULTICAST_DELEGATE(FOnPlayerCharacterDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EPUGameState);

// Enemy blocking ability
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBlockedSignature, bool);

// Targeting icon
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetedSignature, bool);

// Damage system | Health Component
UENUM(BlueprintType)
enum class EPUDamageType : uint8
{
	None = 0,
	Melee,
	Projectile,
	Explosion,
	Environment,
	MAX = 5
};

UENUM(BlueprintType)
enum class EPUDamageResponse : uint8
{
	None = 0,
	Hit,
	Stagger,
	Stun,
	KnockBack,
	MAX = 5
};

USTRUCT(BlueprintType)
struct FPUDamageInfo
{
	GENERATED_USTRUCT_BODY()

public:
	float DamageAmount;

	EPUDamageType DamageType;
	EPUDamageResponse DamageResponse;
	uint8 bIsDamageInvincible : 1;
	uint8 bCanBeParried : 1;
	uint8 bCanBeBlocked : 1;
	uint8 bShouldForceInterrupt : 1;
};

// AI
UENUM(BlueprintType)
enum class EPUAISense : uint8
{
	None = 0,
	Sight,
	Hearing,
	Damage,
	MAX = 4 UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EPUAISense, EPUAISense::MAX);

UENUM(BlueprintType)
enum class EPUAIState : uint8
{
	Passive = 0,
	Attacking,
	Investigating,
	Stun,
	Dead,
	MAX = 5 UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EPUAIState, EPUAIState::MAX);

UENUM(BlueprintType)
enum class EPUAIMovementState : uint8
{
	Idle = 0,
	Walking,
	Jogging,
	Sprinting,
	MAX = 4 UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EPUAIMovementState, EPUAIMovementState::MAX);
