#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReflectionSystemTest.generated.h"

UCLASS()
class SPARTAPROJECT_API AReflectionSystemTest : public AActor
{
	GENERATED_BODY()
	
public:	
	AReflectionSystemTest();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Properties")
	float RotationSpeed;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float MinZ;
	float MaxZ;
	float MoveDirectionZ;

	UFUNCTION(BlueprintCallable, Category = "Item|Action")
	void ResetActorPosition();

	UFUNCTION(BlueprintPure, Category = "Item|Properties")
	float GetRotationSpeed() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Item|Event")
	void OnItemPickedUP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float SpeedZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float SpeedScale; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MinScale; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MaxScale;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	FVector CurrentScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	float NextZ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	FVector CurrentLocation;
};
