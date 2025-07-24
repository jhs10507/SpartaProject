#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"

class ASpawnVolume;
class ASpartaPlayerController;
class ASpartGameInstance;
class USpartaGameInstance;
//class FOnWaveStarted;


UCLASS()
class SPARTAPROJECT_API ASpartaGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASpartaGameState();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;	// 소환된 코인 갯수 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;	// 획득한 코인 갯수

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;	// 레벨 불러오는 시간

	// 현재 레벨 주소
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;	
	
	// 최대 레벨
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;			

	// 레벨 이름 배열
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	FTimerHandle LevelTimerHandle;        // 레벨 타이머 핸들
	FTimerHandle HUDUpdateTimerHandle;    // HUD 타이머 핸들

	// 정수형 점수 얻어오기
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	// 현재 점수에 추가하기
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	// 게임이 끝났을 때 처리할 것들
	UFUNCTION(BlueprintCallable, Category = "Levle")
	void OnGameOver();

	void StartLevel();			// 시작 레벨
	void OnLevelTimeUp();		// 레벨의 시간이 끝났을 때
	void OnCoinCollected();		// 코인 모으기 (점수 계산)
	void EndLevel();			// 레벨이 끝났을 때
	void UpdateHUD();			// UI 표시 갱신


	// 현재 웨이브 주소
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;

	// 최대 웨이브 횟수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWaves;

	// 웨이브 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveDuration;

	// 웨이브당 생성되는 항목 수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TArray<int32> ItemsToSpawnPerWave;

	void StartWave(); // 웨이브 시작
	void EndWave();   // 웨이브 끝
	void OnWaveTimeUp();  // 웨이브 시간 끝났을 때

	FTimerHandle WaveTimerHandle;		// 웨이브 타임 시간 측정

	

private:
	UPROPERTY()
	TArray<AActor*> CurrentWaveItem;

	void EnableWave2(); // 두 번째 웨이브
	void EnableWave3(); // 세 번째 웨이브
	void SetAllCoinsMove(bool bActive);	// 모든 코인의 위치를 변경

	ASpawnVolume* GetSpawnVolume();
	USpartaGameInstance* GetSpartaGameInstace() const;
};