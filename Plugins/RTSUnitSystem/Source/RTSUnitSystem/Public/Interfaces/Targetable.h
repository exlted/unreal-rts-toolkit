// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/FSide.h"
#include "UObject/Interface.h"
#include "Targetable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSUNITSYSTEM_API UTargetable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API ITargetable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FSide GetSide() = 0;
};
