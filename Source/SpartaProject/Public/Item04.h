#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"                 // 오디오 관련 호출 시 필요한 헤더
#include "Particles/ParticleSystemComponent.h"         // 파티클 관련 호출 시 필요한 헤더
#include "Item04.generated.h"

UCLASS()
class SPARTAPROJECT_API AItem04 : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem04();

protected:
	USceneComponent* SceneRoot;
	UAudioComponent* AudioComp;                       // 오디오 컴포넌트
	UStaticMeshComponent* StaticMeshComp;
	UParticleSystemComponent* ParticleComp;           // 파티클 컴포넌트
};
