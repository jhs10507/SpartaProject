#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_LogTest02.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HYUNSU, Warning, All);

UCLASS()
class SPARTAPROJECT_API AItem_LogTest02 : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem_LogTest02();

protected:
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
