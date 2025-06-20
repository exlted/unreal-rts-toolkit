﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/FSide.h"
#include "UObject/Interface.h"
#include "Spawnable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSUNITSYSTEM_API USpawnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API ISpawnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetSide(const FSide NewSide) = 0;
	virtual void SetTableRow(const FDataTableRowHandle) = 0;
};
