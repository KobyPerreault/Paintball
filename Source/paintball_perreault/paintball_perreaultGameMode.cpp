// Copyright Epic Games, Inc. All Rights Reserved.

#include "paintball_perreaultGameMode.h"
#include "paintball_perreaultHUD.h"
#include "paintball_perreaultCharacter.h"
#include "UObject/ConstructorHelpers.h"

Apaintball_perreaultGameMode::Apaintball_perreaultGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Apaintball_perreaultHUD::StaticClass();
}
