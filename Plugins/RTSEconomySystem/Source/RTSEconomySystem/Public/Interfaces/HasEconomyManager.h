// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasEconomyManager.generated.h"

class UPlayerEconomyManager;
// This class does not need to be modified.
UINTERFACE(BlueprintType, NotBlueprintable)
class RTSECONOMYSYSTEM_API UHasEconomyManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSECONOMYSYSTEM_API IHasEconomyManager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual UPlayerEconomyManager* GetEconomyManager() = 0;
};
