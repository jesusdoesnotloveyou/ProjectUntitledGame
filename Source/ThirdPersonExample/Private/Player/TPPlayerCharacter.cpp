// Project Untitled Game by JDNLY. All Rights Reserved.

#include "Player/TPPlayerCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TPBaseCharacterMovementComponent.h"
#include "Components/TPWeaponComponent.h"
#include "Components/TPHealthComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include <Interfaces/CombatSystem/Attackable.h>

DEFINE_LOG_CATEGORY_STATIC(LogTPPlayerCharacter, All, All);

ATPPlayerCharacter::ATPPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = 1; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 420.f;
	GetCharacterMovement()->AirControl = 0.1f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->SetCrouchedHalfHeight(55.0f);

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 250.0f; // The camera follows at this distance behind the character	
	SpringArmComponent->SocketOffset = FVector(0.0f, 50.0f, 25.0f);
	SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow (third person) camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	ThirdPersonCamera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	ThirdPersonCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a follow (first person) camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(GetMesh(), "head"); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetRelativeLocation(FVector(10.0f, 15.0f, 0.0f));
	FirstPersonCamera->SetRelativeRotation(FRotator(-90.0f, 90.0f, 0.0f));

	// Just for testing
	LifeSpanOnDeath = 4.0f;
}

void ATPPlayerCharacter::OnDeath()
{
	Super::OnDeath();
	if (Controller)
		DisableInput(Cast<APlayerController>(Controller));

	PlayAnimMontage(DeathAnimMontage);
}

void ATPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ATPPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ATPPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TryChangeSprintState();

	if (bIsTargeting)
	{
		const auto HealthComp = TargetActor->GetComponentByClass<UTPHealthComponent>();

		// Too comprehensive condition. Should be rewrited in the future
		if (IsWeaponEquiped() && HealthComp && !HealthComp->IsDead()
			&& FVector::Distance(GetActorLocation(), TargetActor->GetActorLocation()) < MaxDistanceToTarget)
		{
			if (!GetController()) return;

			const auto LookAtTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
			const auto CurrentRotation = Controller->GetControlRotation();
			Controller->SetControlRotation(UKismetMathLibrary::RInterpTo(CurrentRotation, LookAtTarget, DeltaTime, CameraTargetingRotationSpeed));
			
			const auto WeaponComp = TargetActor->GetComponentByClass<UTPWeaponComponent>();
			if (WeaponComp) WeaponComp->SetTarget(true);
		}
		else
		{
			DisableTargeting();
		}
	}
}

void ATPPlayerCharacter::Destroyed()
{
	Super::Destroyed();
	OnPlayerCharacterDeath.Broadcast();
}

//////////////////////////////////////////////////////////////////////////
// Input
void ATPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		/** Movement */
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATPPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPPlayerCharacter::Look);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ATPPlayerCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ATPPlayerCharacter::StopSprint);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ATPPlayerCharacter::ChangeCrouchState);

		/** Other */
		EnhancedInputComponent->BindAction(PotionAction, ETriggerEvent::Started, this, &ATPPlayerCharacter::UseHealPotion);
		// Switching camera
		EnhancedInputComponent->BindAction(SwitchCameraAction, ETriggerEvent::Started, this, &ATPPlayerCharacter::SwitchCamera);
		/** Combat System */
		// IT MIGHT POSSIBLE to make light/heavy attack in ONLY ONE method
		EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Completed, this, &ATPPlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Completed, this, &ATPPlayerCharacter::HeavyAttack);
		EnhancedInputComponent->BindAction(EquipWeaponAction, ETriggerEvent::Started, this, &ATPPlayerCharacter::EquipWeapon);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ATPPlayerCharacter::Roll);
		// Targeting
		EnhancedInputComponent->BindAction(LockOnTargetAction, ETriggerEvent::Started, this, &ATPPlayerCharacter::LockOnTarget);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Started, this, &ATPPlayerCharacter::StartBlocking);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Completed, this, &ATPPlayerCharacter::StopBlocking);

	}
	else
	{
		UE_LOG(LogTPPlayerCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}

void ATPPlayerCharacter::Jump()
{
	// TO DO: make up smth
	if (IsWeaponEquiped()) return;
	//if (bIsAttacking || bIsRolling) return;
	Super::Jump();
}

void ATPPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (!Controller) return;
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
	//AddMovementInput(YawRotation.RotateVector(FVector::ForwardVector), MovementVector.Y);
	//AddMovementInput(YawRotation.RotateVector(FVector::RightVector), MovementVector.X);
}

void ATPPlayerCharacter::Look(const FInputActionValue& Value)
{
	if (bIsTargeting) return;
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (!Controller) return;

	// add yaw and pitch input to controller
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ATPPlayerCharacter::StartSprint(const FInputActionValue& Value)
{
	if (IsWeaponEquiped()) return;
	UE_LOG(LogTPPlayerCharacter, Warning, TEXT("Sprint input action is called"));
	bIsSprintRequested = true;
	//bIsLockedOnTarget = false;
	/*if (bIsCrouched) {
		UnCrouch();
	}*/
	OnSprintStart();
}

void ATPPlayerCharacter::StopSprint(const FInputActionValue& Value)
{
	bIsSprintRequested = false;
	OnSprintEnd();
}

bool ATPPlayerCharacter::CanSprint()
{
	return !BaseCharacterMovement->IsCrouching();
}

void ATPPlayerCharacter::TryChangeSprintState()
{
	bool bIsSprintActive = AbilitySystemComponent->IsAbilityActive(SprintAbilityTag);

	if (bIsSprintRequested && !bIsSprintActive && !BaseCharacterMovement->IsSprinting() && CanSprint())
	{
		if (AbilitySystemComponent->TryActivateAbilitiesWithTag(SprintAbilityTag))
		{
			OnSprintStart();
		}
	}

	if (!(bIsSprintRequested && CanSprint()) && bIsSprintActive) {
		if (AbilitySystemComponent->TryCancelAbilitiesWithTag(SprintAbilityTag))
		{
			OnSprintEnd();
		}
	}
}

void ATPPlayerCharacter::ChangeCrouchState(const FInputActionValue& Value)
{
	UE_LOG(LogTPPlayerCharacter, Warning, TEXT("Crouching input action is called"));

	if (AbilitySystemComponent->IsAbilityActive(CrouchAbilityTag))
	{
		AbilitySystemComponent->TryActivateAbilitiesWithTag(CrouchAbilityTag);
	}
	else {
		UnCrouch();
	}
}

void ATPPlayerCharacter::UseHealPotion()
{
	if (IsRolling()) return;
	HealthComponent->UseHealPotion();
}

void ATPPlayerCharacter::Roll(const FInputActionValue& Value)
{
	if (BaseCharacterMovement->IsFalling() || BaseCharacterMovement->Velocity.IsNearlyZero()) return;
	WeaponComponent->Roll();
}

void ATPPlayerCharacter::SwitchCamera(const FInputActionValue& Value)
{
	bool bSwitchCamera = Value.Get<bool>();
	UE_LOG(LogTPPlayerCharacter, Warning, TEXT("Switching camera input action is called"));

	if (ThirdPersonCamera->IsActive()) {
		ThirdPersonCamera->SetActive(!bSwitchCamera);
		FirstPersonCamera->SetActive(bSwitchCamera);
		bUseControllerRotationYaw = bSwitchCamera;
	}
	else {
		FirstPersonCamera->SetActive(!bSwitchCamera);
		ThirdPersonCamera->SetActive(bSwitchCamera);
		bUseControllerRotationYaw = !bSwitchCamera;
	}
}

void ATPPlayerCharacter::Attack(const FInputActionValue& Value)
{
	if (!CanAttack()) return;
	WeaponComponent->Attack();
}

void ATPPlayerCharacter::HeavyAttack(const FInputActionValue& Value)
{
	if (!CanAttack()) return;
	WeaponComponent->HeavyAttack();
}

void ATPPlayerCharacter::StartBlocking(const FInputActionValue& Value)
{
	if (!IsWeaponEquiped()) return;
	
	bUseControllerRotationYaw = true;
	WeaponComponent->StartBlocking();
}

void ATPPlayerCharacter::StopBlocking(const FInputActionValue& Value)
{
	if (!IsWeaponEquiped()) return;

	bUseControllerRotationYaw = false;
	WeaponComponent->StopBlocking();
}

void ATPPlayerCharacter::EquipWeapon(const FInputActionValue& Value)
{
	WeaponComponent->EquipWeapon();
}

bool ATPPlayerCharacter::CanAttack()
{
	if (BaseCharacterMovement->IsSprinting() || BaseCharacterMovement->IsFalling()) return false;
	return true;
}

void ATPPlayerCharacter::LockOnTarget()
{
	if (!bIsTargeting && IsWeaponEquiped()) 
	{
		if (!GetWorld()) return;

		FHitResult OutHit;
		FVector TraceStart = GetActorLocation();
		FVector CameraRotationVector = ThirdPersonCamera->GetComponentRotation().Vector();
		FVector TraceEnd = TraceStart + TargetingDistance * FVector(CameraRotationVector.X, CameraRotationVector.Y, 0.0);

		FQuat Rot = FQuat();
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		if (!GetWorld()->SweepSingleByChannel(OutHit, TraceStart, TraceEnd, Rot,
			ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(TargetingSphereCollisionRadius), CollisionParams))
			return;

		// In more general case, we should check if it is an enemy
		TargetActor = OutHit.GetActor() ? OutHit.GetActor() : nullptr;
		if (TargetActor) bIsTargeting = true;
	}
	else
	{
		DisableTargeting();
	}

}

void ATPPlayerCharacter::DisableTargeting()
{
	if (TargetActor)
	{
		const auto WeaponComp = TargetActor->GetComponentByClass<UTPWeaponComponent>();
		if (WeaponComp) WeaponComp->SetTarget(false);
	}
	TargetActor = nullptr;
	bIsTargeting = false;
}

void ATPPlayerCharacter::OnSprintStart_Implementation() {}

void ATPPlayerCharacter::OnSprintEnd_Implementation() {}

void ATPPlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	SpringArmComponent->TargetOffset += FVector(0.0f, 0.0f, HalfHeightAdjust);
}

void ATPPlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	SpringArmComponent->TargetOffset -= FVector(0.0f, 0.0f, HalfHeightAdjust);
}

bool ATPPlayerCharacter::CanJumpInternal_Implementation() const
{
	// look at the 3091 line in UCharacterMovementComponent void Crouch(bool bClientSimulation)
	// to add check for free space under character to jump
	return bIsCrouched || Super::CanJumpInternal_Implementation();
}

void ATPPlayerCharacter::OnJumped_Implementation()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
}