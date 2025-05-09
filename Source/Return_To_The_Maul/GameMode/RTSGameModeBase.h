// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API ARTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = L"") override;

	UPROPERTY(EditAnywhere)
	int TeamNumber = 0;

	UPROPERTY(EditAnywhere)
	TArray<FColor> TeamColors = {
			FColor( 255, 0, 0, 255),
			FColor(0, 255, 0, 255),
			FColor(0, 0, 255, 255),
			FColor(255, 255, 0, 255),
			FColor(255, 0, 255, 255),
			FColor(0, 255, 255, 255),
			FColor(255, 255, 255, 255),
			FColor(0, 0, 0, 255),
		};
};
