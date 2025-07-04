#include "ReflectionSystemTest.h"


AReflectionSystemTest::AReflectionSystemTest()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Couch.SM_Couch"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Gem_A.M_Gem_A"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;

	SpeedZ = 200.0f;
	MinZ = 0.0f;
	MaxZ = 400.0f;
	MoveDirectionZ = 1.0f;

	RotationSpeed = 90.0f;
	SpeedScale = 1.0f;
	CurrentScale = FVector(1.0f);
	MinScale = 1.0f;
	MaxScale = 3.0f;
}

void AReflectionSystemTest::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
	StaticMeshComp->SetRelativeScale3D(CurrentScale);

	OnItemPickedUP();
}

void AReflectionSystemTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation = GetActorLocation();

	NextZ = CurrentLocation.Z + SpeedZ * DeltaTime * MoveDirectionZ;

	if (NextZ > MaxZ)
	{
		NextZ = MaxZ;
		MoveDirectionZ = -1.0f;
	}
	else if (NextZ < MinZ)
	{
		NextZ = MinZ;
		MoveDirectionZ = 1.0f;
	}

	SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, NextZ));

	//AddActorLocalOffset(FVector(0.0f, 0.0f, SpeedZ * DeltaTime));
	AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));

	if (!FMath::IsNearlyZero(SpeedScale * DeltaTime))
	{
		CurrentScale += FVector(FMath::Sin(SpeedScale * DeltaTime));
		StaticMeshComp->SetRelativeScale3D(CurrentScale);
	}

	if (CurrentScale.X >= MaxScale || CurrentScale.X <= MinScale)
	{
		SpeedScale *= -1;
	}

	/*if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}*/
}

void AReflectionSystemTest::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float AReflectionSystemTest::GetRotationSpeed() const
{
	return RotationSpeed;
}