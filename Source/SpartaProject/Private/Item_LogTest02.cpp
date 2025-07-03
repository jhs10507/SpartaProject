#include "Item_LogTest02.h"

DEFINE_LOG_CATEGORY(HYUNSU);

// Sets default values
AItem_LogTest02::AItem_LogTest02()
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

	UE_LOG(HYUNSU, Warning, TEXT("%s 컨스트럭트"), *GetName());
}

void AItem_LogTest02::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UE_LOG(HYUNSU, Warning, TEXT("%s 이니셜라이즈 컴포넌트"), *GetName());
}

// Called when the game starts or when spawned
void AItem_LogTest02::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(HYUNSU, Warning, TEXT("%s 플레이 시작"), *GetName());
}

// Called every frame
void AItem_LogTest02::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem_LogTest02::Destroyed()
{
	UE_LOG(HYUNSU, Warning, TEXT("%s 삭제"), *GetName());
}

void AItem_LogTest02::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(HYUNSU, Warning, TEXT("%s 끝"), *GetName());

	Super::EndPlay(EndPlayReason);
}