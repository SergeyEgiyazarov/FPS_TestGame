// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_TestGameGameMode.h"
#include "FPS_TestGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_TestGameGameMode::AFPS_TestGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
