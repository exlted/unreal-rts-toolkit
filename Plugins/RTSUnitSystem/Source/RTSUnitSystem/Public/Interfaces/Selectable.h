﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/UnitRelationType.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSUNITSYSTEM_API USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API ISelectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void OnSelect() = 0;
	virtual void OnDeselect() = 0;
	virtual bool HasTag(FName TagName) = 0;
};
