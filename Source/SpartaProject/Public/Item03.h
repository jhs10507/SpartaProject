// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item03.generated.h"

UCLASS()
class SPARTAPROJECT_API AItem03 : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem03();

protected:
	/*virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;*/

	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;
};
