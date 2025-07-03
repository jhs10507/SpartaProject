#include "Item02.h"


AItem02::AItem02()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
}

void AItem02::BeginPlay()
{
	Super::BeginPlay();
	
	OnItemPickedUP();
}

void AItem02::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}

void AItem02::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float AItem02::GetRotationSpeed() const
{
	return RotationSpeed;
}