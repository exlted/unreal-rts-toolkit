// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ModularPlayerController.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSPLAYERCONTROLLER_API UModularPlayerController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSPLAYERCONTROLLER_API IModularPlayerController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TArray<FName> GetNamedComponents() = 0;
	virtual void PushNamedComponent(FName Name) = 0;
	// Returns False when no Components left in Stack
	virtual bool PopComponent() = 0;
};
