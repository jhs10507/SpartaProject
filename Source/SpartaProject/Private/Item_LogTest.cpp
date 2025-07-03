#include "Item_LogTest.h"

DEFINE_LOG_CATEGORY(LogSparta);

AItem_LogTest::AItem_LogTest()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Couch.SM_Couch"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/Resources/Materials/M_Gem_A.M_Gem_A"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	UE_LOG(LogSparta, Warning, TEXT("%s Constructor"), *GetName());
}

void AItem_LogTest::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UE_LOG(LogSparta, Warning, TEXT("%s PostInitializeComponents"), *GetName());
}

void AItem_LogTest::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());
}

void AItem_LogTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem_LogTest::Destroyed()
{
	UE_LOG(LogSparta, Warning, TEXT("%s Destroyed"), *GetName());
}

void AItem_LogTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogSparta, Warning, TEXT("%s EndPlay"), *GetName());

	Super::EndPlay(EndPlayReason);
}