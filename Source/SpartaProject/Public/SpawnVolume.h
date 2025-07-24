#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

// 박스 컴포넌트 클래스
class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();
	
	// 씬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	
	// 소환하는 박스 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;

	// 아이템 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* ItemDataTable;								// 아이템 데이터 테이블

	// 액터를 랜덤하게 소환
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();

	// 볼륨 안에서 랜덤하게 생성
	FItemSpawnRow* GetRandomItem() const;
	FVector GetRandomPointInVolume() const;					// 벡터 위치값
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);			// 아이템 테이블

	AActor* GetSpawnVolume() const;
};
