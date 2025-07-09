#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASpartaCharacter::ASpartaCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0.0f, 40.0f, 15.0f);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = 
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = 
			Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction, 
					ETriggerEvent::Triggered, 
					this, 
					&ASpartaCharacter::Move
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered, 
					this, 
					&ASpartaCharacter::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed, 
					this,
					&ASpartaCharacter::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered, 
					this, 
					&ASpartaCharacter::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered, 
					this, 
					&ASpartaCharacter::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed, 
					this, 
					&ASpartaCharacter::StopSprint
				);
			}
		}
	}
}

void ASpartaCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}
void ASpartaCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
		UE_LOG(LogTemp, Warning, TEXT("Jump"));
	}
}
void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
		UE_LOG(LogTemp, Warning, TEXT("Landing"));
	}
}
void ASpartaCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}
void ASpartaCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Fast"));
	}
}
void ASpartaCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Slow"));
	}
}
