#include "SpartaPawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASpartaPawn::ASpartaPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 100.0f;
	Direction = FVector::ZeroVector;
	ForwardInput;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0.0f, 40.0f, 15.0f);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
}

void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PlayerInputComponent->BindAxis(
			TEXT("MoveForward"),
			this,
			&ASpartaPawn::MoveForward
		);
	}
}

void ASpartaPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASpartaPawn::MoveForward(float Value)
{
	ForwardInput = Value;
}

void ASpartaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Move = FVector::ForwardVector * MoveSpeed * DeltaTime;
	AddActorLocalOffset(Move, true);
	//AddMovementInput(Direction, (MoveSpeed * DeltaTime), true);
	
}