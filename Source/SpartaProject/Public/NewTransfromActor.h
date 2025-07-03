#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NewTransfromActor.generated.h"

UCLASS()
class SPARTAPROJECT_API ANewTransfromActor : public AActor
{
	GENERATED_BODY()
	
public:
	ANewTransfromActor();

protected:
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float SpeedZ;
	float RotationSpeed;
	float SpeedScale, MinScale, MaxScale;
	FVector CurrentScale;
};
