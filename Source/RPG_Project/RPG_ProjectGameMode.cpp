// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RPG_Project.h"
#include "RPG_ProjectGameMode.h"
#include "RPG_ProjectPlayerController.h"
#include "RPG_ProjectCharacter.h"

ARPG_ProjectGameMode::ARPG_ProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARPG_ProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}