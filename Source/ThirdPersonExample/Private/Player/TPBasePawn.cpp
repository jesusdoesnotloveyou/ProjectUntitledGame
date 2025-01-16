// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/TPBasePawn.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TPBasePawnMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPBasePawn, All, All);

ATPBasePawn::ATPBasePawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->SetSphereRadius(50.0f);
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UTPBasePawnMovementComponent>("MovementComponent");
	MovementComponent->SetUpdatedComponent(CollisionComponent);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(CollisionComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 500.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

void ATPBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATPBasePawn::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATPBasePawn::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPBasePawn::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPBasePawn::Look);
	}
}

float ATPBasePawn::GetCollisionSphereRadius() const
{
	return CollisionComponent->GetUnscaledSphereRadius();
}

void ATPBasePawn::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector MoveVector = Value.Get<FVector>();
	AddMovementInput(GetActorForwardVector(), MoveVector.Y);
	AddMovementInput(GetActorRightVector(), MoveVector.X);
}

void ATPBasePawn::Look(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector LookVector = Value.Get<FVector>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ATPBasePawn::Jump(const FInputActionValue& Value)
{
	checkf(MovementComponent->IsA<UTPBasePawnMovementComponent>(), TEXT("ATPBasePawn::Jump can perform only on UTPBasePawnMovementComponent"));
	bPressedJump = true;
	UTPBasePawnMovementComponent* BasePawnMovementComponent = StaticCast<UTPBasePawnMovementComponent*>(MovementComponent);
	if (!BasePawnMovementComponent) return;
	BasePawnMovementComponent->JumpStart();

	UE_LOG(LogTPBasePawn, Warning, TEXT("Jump called"));
}

void ATPBasePawn::StopJumping(const FInputActionValue& Value)
{
	bPressedJump = false;
}
