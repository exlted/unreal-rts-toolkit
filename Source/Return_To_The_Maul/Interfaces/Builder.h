// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Builder.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBuilder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RETURN_TO_THE_MAUL_API IBuilder
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// TODO: Change from UClass* to the correct class for ONLY building information
	TArray<UClass*> GetBuildableObjects();
};
