// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MoveUnit.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSTOOLKITINTERFACES_API UMoveUnit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSTOOLKITINTERFACES_API IMoveUnit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void MoveSelectedUnit(const FVector& GoalPosition, const int Sender = -1) = 0;
};
