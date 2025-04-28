// Copyright Epic Games, Inc. All Rights Reserved.

#include "Return_To_The_MaulGameMode.h"
#include "Return_To_The_MaulPlayerController.h"
#include "Return_To_The_MaulCharacter.h"
#include "UObject/ConstructorHelpers.h"

AReturn_To_The_MaulGameMode::AReturn_To_The_MaulGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AReturn_To_The_MaulPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownMyPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}