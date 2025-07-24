#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "SpartaPlayerController.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

// 전체 초기화
ASpartaGameState::ASpartaGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;

	// 현재 웨이브 주소값
	CurrentWaveIndex = 0;
	// 최대 웨이브 횟수
	MaxWaves = 3;
	// 웨이브 시간
	WaveDuration = 10.0f;
	// 웨이브당 생성되는 항목 수
	ItemsToSpawnPerWave = {20, 30, 40};
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	//UpdateHUD();
	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ASpartaGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	// 점수 표시
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			SpartaGameInstance->AddToScore(Amount);
		}
	}
}

// 게임 시작시 초기화
void ASpartaGameState::StartLevel()
{


	// 플레이어 HUD 표시
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		// 게임 인스턴스를 현재 레벨 인덱스에 사용
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
			UE_LOG(LogTemp, Warning, TEXT("현재 레벨 인덱스: %d"), CurrentLevelIndex);
		}
	}

	CurrentWaveIndex = 0;
	StartWave();

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);
}

void ASpartaGameState::OnLevelTimeUp()
{
	EndLevel();
}

void ASpartaGameState::OnCoinCollected()
{
	//CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), 
		CollectedCoinCount,
		SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndWave();
	}
}

void ASpartaGameState::EndLevel()
{
	// 타이머 헤제
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (USpartaGameInstance* SpartaGameInstance = GetSpartaGameInstace())
	{

		AddScore(Score);
		CurrentLevelIndex++; // 레벨 인덱스 값 증가
		SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		UE_LOG(LogTemp, Warning, TEXT("현재 레벨 인덱스: %d"), CurrentLevelIndex);

		// 모든 레벨을 다 돌면 게임 오버
		if (CurrentLevelIndex >= MaxLevels)
		{
			OnGameOver();
			return;
		}

		// 레벨 이름 주소가 맞으면
		if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
		{
			UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
			UE_LOG(LogTemp, Warning, TEXT("레벨 불러오기 시도"));
		}
		else
		{
			OnGameOver();
		}
	}
}

// 게임 오버 화면
void ASpartaGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->SetPause(true);
			SpartaPlayerController->ShowMainMenu(true);
		}
	}
}

void ASpartaGameState::UpdateHUD()
{
	// 월드의 첫 번째 플레이어 컨트롤러를 가져옴
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			// 플레이어 컨트롤러의 위젯
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())
			{
				// 위젯 이름 출력
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					// GetTimerRemaining : 시간이 얼마 남았는지를 알려줌
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					// 남은 시간을 문자열로 표시해줌.
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
				}
				// 점수
				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
						if (SpartaGameInstance)
						{
							ScoreText->SetText(FText::FromString(
								FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
						}
					}
				}
				// 레벨
				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					// 현재 레벨을 문자열로 표시해줌.
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
				}
				// 웨이브
				if (UTextBlock* WaveIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
				{
					// 현재 레벨을 문자열로 표시해줌.
					WaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d"), CurrentWaveIndex + 1)));
				}

			}
		}
	}
}

// 웨이브 시작
void ASpartaGameState::StartWave()
{
	// 소환될 코인 숫자
	SpawnedCoinCount = 0;
	// 획득한 코인 숫자
	CollectedCoinCount = 0;

	// 아이템 액터는 웨이브 아이템 값만큼 호출
	for (AActor* Item : CurrentWaveItem)
	{
		// 이전 레벨의 아이템들은 삭제
		if (Item && Item->IsValidLowLevelFast())
		{
			Item->Destroy();
		}
	}
	// 현재 웨이브 아이템은 비우기
	CurrentWaveItem.Empty();

	// 아이템 소환은 웨이브의 주소를 확인해서, 맞으면 호출하고, 틀리면 20으로
	int32 ItemToSpawn = (ItemsToSpawnPerWave.IsValidIndex(CurrentWaveIndex)) ?
		ItemsToSpawnPerWave[CurrentWaveIndex] : 20;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	if (FoundVolumes.Num() > 0)
	{
		if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
		{
			for (int32 i = 0; i < ItemToSpawn; i++)
			{
				// 소환된 액터는 소환 볼륨에서 랜덤하게 소환된 아이템
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();

				// 소환된 액터가 코인이라면 코인 카운트 증가
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	if (CurrentWaveIndex == 1)
	{
		EnableWave2();
	}
	else if (CurrentWaveIndex == 2)
	{
		EnableWave3();
	}

	// 월드 타이머를 통해 웨이브 시간 측정
	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&ASpartaGameState::OnWaveTimeUp,
		WaveDuration,
		false
	);
}

void ASpartaGameState::EnableWave2()
{
	const FString Msg = TEXT("Wave 2");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

	if (ASpawnVolume* SpawnVolume = GetSpawnVolume())
	{
		for (int32 i = 0; i < 15; i++)
		{
			if (AActor* SpawnedActor = SpawnVolume->SpawnRandomItem())
			{
				// 소환된 액터가 코인이라면 코인 카운트 증가
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}
}

void ASpartaGameState::EnableWave3()
{
	const FString Msg = TEXT("Wave 2");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

	SetAllCoinsMove(true);
}

void ASpartaGameState::OnWaveTimeUp()
{
	EndWave();
}

void ASpartaGameState::EndWave()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	if (CurrentWaveIndex == 2)
	{
		SetAllCoinsMove(false);
	}

	++CurrentWaveIndex;
	if (CurrentWaveIndex >= MaxWaves)
	{
		EndWave();
	}
	else
	{
		StartWave();
	}
}

ASpawnVolume* ASpartaGameState::GetSpawnVolume()
{
	TArray<AActor*> FoundVolumes;
	// 모든 액터들 중에서 지정한 액터 클래스를 불러옴
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	// 검색한 소환 볼륨을 캐스트
	//ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);

	// 찾은 볼륨 숫자가 0보다 크면 불러오고 아니면 스킵
	return (FoundVolumes.Num() > 0) ? Cast<ASpawnVolume>(FoundVolumes[0]) : nullptr;
}

void ASpartaGameState::SetAllCoinsMove(bool bActivate)
{
	for (AActor* CoinActor : CurrentWaveItem)
	{
		if (ACoinItem* Coin = Cast<ACoinItem>(CoinActor))
		{
			Coin;
		}
	}
}

USpartaGameInstance* ASpartaGameState::GetSpartaGameInstace() const
{
	return Cast<USpartaGameInstance>(GetGameInstance());
}