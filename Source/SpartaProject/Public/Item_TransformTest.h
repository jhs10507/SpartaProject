#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_TransformTest.generated.h"

UCLASS()
class SPARTAPROJECT_API AItem_TransformTest : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem_TransformTest();

protected:
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
