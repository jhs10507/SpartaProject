#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ASpartaPlayerController::ASpartaPlayerController()
	: InputMappingContext(nullptr)
	, MoveAction(nullptr)
	, JumpAction(nullptr)
	, LookAction(nullptr)
	, SprintAction(nullptr)
	, ShowUI(nullptr)
{
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = 
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
			if (!InputMappingContext)
			{
				SubSystem->RemoveMappingContext(InputMappingContext);
				SubSystem->AddMappingContext(ShowUI, 0);
				UE_LOG(LogTemp, Warning, TEXT("ShowUI"));
			}
		}
	}
}