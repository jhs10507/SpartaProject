#include "NewTransfromActor.h"


ANewTransfromActor::ANewTransfromActor()
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
	RotationSpeed = 90.0f;
	SpeedScale = 1.0f;
	CurrentScale = FVector(1.0f);
	MinScale = 1.0f;
	MaxScale = 3.0f;
}

void ANewTransfromActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
	StaticMeshComp->SetRelativeScale3D(CurrentScale);
}

void ANewTransfromActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(0.0f, 0.0f, SpeedZ * DeltaTime));
	AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));

	if (!FMath::IsNearlyZero(SpeedScale * DeltaTime))
	{
		CurrentScale += FVector(FMath::Sin(SpeedScale));
		StaticMeshComp->SetRelativeScale3D(CurrentScale);
	}

	if (CurrentScale.X >= MaxScale || CurrentScale.X <= MinScale)
	{
		SpeedScale *= -1;
	}
}

