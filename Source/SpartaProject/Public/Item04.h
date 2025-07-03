#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Item04.generated.h"

UCLASS()
class SPARTAPROJECT_API AItem04 : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem04();

protected:
	USceneComponent* SceneRoot;
	UAudioComponent* AudioComp;
	UStaticMeshComponent* StaticMeshComp;
	UParticleSystemComponent* ParticleComp;
};
