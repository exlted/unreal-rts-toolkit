// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameModeBase.h"

#include "BasePlayerController.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Return_To_The_Maul/Player/BasePlayerState.h"

FString ARTSGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                        const FString& Options, const FString& Portal)
{
	check(NewPlayerController);

	// The player needs a PlayerState to register successfully
	if (NewPlayerController->PlayerState == nullptr)
	{
		return FString(TEXT("PlayerState is null"));
	}

	// Register the player with the session
	GameSession->RegisterPlayer(NewPlayerController, UniqueId, UGameplayStatics::HasOption(Options, TEXT("bIsFromInvite")));

	// Find a starting spot
	FString ErrorMessage;
	if (!UpdatePlayerStartSpot(NewPlayerController, Portal, ErrorMessage))
	{
		UE_LOG(LogGameMode, Warning, TEXT("InitNewPlayer: %s"), *ErrorMessage);
	}

	// Set up spectating
	const bool bSpectator = FCString::Stricmp(*UGameplayStatics::ParseOption(Options, TEXT("SpectatorOnly")), TEXT("1")) == 0;
	if (bSpectator || MustSpectate(NewPlayerController))
	{
		NewPlayerController->StartSpectatingOnly();
	}

	// Init player's name
	FString InName = UGameplayStatics::ParseOption(Options, TEXT("Name")).Left(20);
	if (InName.IsEmpty())
	{
		InName = FString::Printf(TEXT("%s%i"), *DefaultPlayerName.ToString(), NewPlayerController->PlayerState->GetPlayerId());
	}

	ChangeName(NewPlayerController, InName, false);

	// Original Function Above (Don't want to double up on these checks)

	if (!bSpectator)
	{
		if (ABasePlayerState* PlayerState = NewPlayerController->GetPlayerState<ABasePlayerState>(); PlayerState != nullptr)
		{
			PlayerState->SetColor(TeamColors[TeamNumber % TeamColors.Num()]);
			PlayerState->SetPlayerNum(TeamNumber++);
			PlayerState->SpawnEntities(FTransform(NewPlayerController->GetSpawnLocation()));
		}
	}
	
	return ErrorMessage;
}
