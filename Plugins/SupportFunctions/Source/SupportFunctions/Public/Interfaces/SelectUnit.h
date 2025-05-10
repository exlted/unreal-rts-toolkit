// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/ESelectStyle.h"
#include "UObject/Interface.h"
#include "SelectUnit.generated.h"

// This class does not need to be modified.
UINTERFACE()
class SUPPORTFUNCTIONS_API USelectUnit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SUPPORTFUNCTIONS_API ISelectUnit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SelectUnit(AActor* SelectedUnit, ESelectStyle SelectionStyle, int Sender = -1) = 0;
};
