// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/AutoSpawner.h"
#include "Interfaces/GameController.h"
#include "RTSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API ARTSGameModeBase : public AGameModeBase, public IGameController
{
	GENERATED_BODY()

public:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = L"") override;

	virtual void StartNextWave() override;
	virtual void RegisterSpawner(TScriptInterface<IAutoSpawner> NewSpawner) override;

	
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

	UPROPERTY(EditAnywhere)
	TArray<TScriptInterface<IAutoSpawner>> Spawners;
};
