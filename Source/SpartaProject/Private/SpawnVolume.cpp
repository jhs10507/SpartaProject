#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

// 스폰 볼륨 생성자
ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	// 스폰 박스는 씬 컴포넌트에
	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawning"));
	SpawningBox->SetupAttachment(Scene);

	// 데이터 테이블은 비워둠
	ItemDataTable = nullptr;
}

// 아이템을 랜덤하게 스폰
AActor* ASpawnVolume::SpawnRandomItem()
{
	// 배열의 아이템을 랜덤하게 불러옴
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		// 아이템 클래스를 가져와 현재 클래스로 
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			// SpawnItem 호출, 스폰된 AActor 포인트 리턴
			return SpawnItem(ActualClass);
		}
	}

	return nullptr;
}

// 아이템을 랜덤하게 가져옴
FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	// 데이터 테이블이 없으면 스킵
	if (!ItemDataTable) return nullptr;

	// 모든 행 가져오기
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));

	// 아이템 데이터 테이블의 모든 행을 가져옴
	ItemDataTable->GetAllRows(ContextString, AllRows);

	// 모든 행이 비였으면 스킵
	if (AllRows.IsEmpty()) return nullptr;

	// 전체 확률 합 구하기
	float TotalChance = 0.0f; // 초기화
	for (const FItemSpawnRow* Row : AllRows) // AllRows 배열의 각 행을 순회
	{
		if (Row) // 행이 유효한지 확인
		{
			TotalChance += Row->Spawnchance; // Spawnchance 값을 TotalChance에 더하기
		}
	}

	// 0 ~ TotalChance 사이 랜덤 값
	const float RandValue = FMath::FRandRange(0.0f, TotalChance); // 초기화
	float AccumulateChance = 0.0f;

	// 누적 확률로 아이템 선택
	for (FItemSpawnRow* Row : AllRows)
	{
		// 아이템의 총합 계산
		AccumulateChance += Row->Spawnchance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}
	// 포인터 변수 초기화?
	return nullptr;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	// 박스의 크기 결정
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	// 박스의 위치 결정
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	// 박스의 위치와 무작위 위치 값 반환
	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

// 액터 아이템들을 불러옴
AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	// 없으면 스킵
	if (!ItemClass) return nullptr;

	// 소환할 액터는 월드의 모든 아이템 클래스이며, 회전 값은 없는 무작위 위치에 배치
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);

	return SpawnedActor;
}