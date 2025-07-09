#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpartaPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SPARTAPROJECT_API ASpartaPawn : public APawn
{
	GENERATED_BODY()

public:
	ASpartaPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);

private:
	float MoveSpeed;
	float ForwardInput;
	FVector Direction;
};
