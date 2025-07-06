#include "SpartaGameMode.h"
#include "SpartaCharacter.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
}