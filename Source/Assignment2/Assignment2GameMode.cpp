// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment2GameMode.h"
#include "Assignment2Character.h"
#include "UObject/ConstructorHelpers.h"

AAssignment2GameMode::AAssignment2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
