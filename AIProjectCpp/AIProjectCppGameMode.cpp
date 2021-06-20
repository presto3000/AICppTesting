// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIProjectCppGameMode.h"
#include "AIProjectCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIProjectCppGameMode::AAIProjectCppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
