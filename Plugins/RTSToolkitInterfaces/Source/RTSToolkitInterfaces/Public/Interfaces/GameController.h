// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interfaces/AutoSpawner.h"
#include "GameController.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSTOOLKITINTERFACES_API UGameController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSTOOLKITINTERFACES_API IGameController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void StartNextWave() = 0;
	virtual void RegisterSpawner(TScriptInterface<IAutoSpawner> NewSpawner) = 0;
};
