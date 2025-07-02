#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item02.generated.h"

UCLASS()
class SPARTAPROJECT_API AItem02 : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem02();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
