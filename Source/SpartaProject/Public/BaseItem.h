#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class SPARTAPROJECT_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;
	// 루트 컴포넌트 (씬)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;
	// 충돌 컴포넌트 (플레이어 진입 범위 감지용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* Collision;
	// 아이템 시각 표현용 스테틱 메시
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;
	
	// 플레이어가 이 아이템의 범위에 들어왔을 때 호출
	virtual void OnItemOverlap(AActor* OverlapActor) override;
	// 플레이어가 이 아이템의 범위를 벗어났을 때 호출
	virtual void OnItemEndOverlap(AActor* OverlapActor) override;
	// 아이템이 사용되었을 때 호출
	virtual void ActivateItem(AActor* OverlapActor) override;
	// 이 아이템의 타입을 반환
	virtual FName GetItemType() const override;
	// 아이템 삭제
	virtual void DestroyItem();
};
