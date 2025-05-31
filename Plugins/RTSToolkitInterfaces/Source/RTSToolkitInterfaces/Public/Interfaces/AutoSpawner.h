// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/Wave.h"
#include "UObject/Interface.h"
#include "AutoSpawner.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSTOOLKITINTERFACES_API UAutoSpawner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSTOOLKITINTERFACES_API IAutoSpawner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SpawnNextWave() = 0;
	virtual bool HasAnotherWave() = 0;
	virtual const FWave& GetNextWave() = 0;
};
