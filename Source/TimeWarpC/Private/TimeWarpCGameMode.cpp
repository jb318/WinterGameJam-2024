// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeWarpCGameMode.h"
#include "TimeWarpCCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATimeWarpCGameMode::ATimeWarpCGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
