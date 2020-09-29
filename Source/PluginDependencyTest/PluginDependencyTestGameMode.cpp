// Copyright Epic Games, Inc. All Rights Reserved.

#include "PluginDependencyTestGameMode.h"
#include "PluginDependencyTestHUD.h"
#include "PluginDependencyTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

APluginDependencyTestGameMode::APluginDependencyTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APluginDependencyTestHUD::StaticClass();
}
