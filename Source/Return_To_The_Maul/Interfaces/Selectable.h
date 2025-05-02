// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RETURN_TO_THE_MAUL_API ISelectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	void OnSelect();
};
