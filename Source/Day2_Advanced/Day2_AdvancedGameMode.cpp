// Copyright Epic Games, Inc. All Rights Reserved.

#include "Day2_AdvancedGameMode.h"
#include "Day2_AdvancedCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADay2_AdvancedGameMode::ADay2_AdvancedGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
