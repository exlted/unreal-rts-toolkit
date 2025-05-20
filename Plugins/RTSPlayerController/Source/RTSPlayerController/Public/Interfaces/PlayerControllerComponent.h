// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "UObject/Interface.h"
#include "PlayerControllerComponent.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSPLAYERCONTROLLER_API UPlayerControllerComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSPLAYERCONTROLLER_API IPlayerControllerComponent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Enable() = 0;
	virtual void Disable() = 0;

	virtual void SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
		UEnhancedInputComponent* EnhancedInputComponent, APlayerController* PlayerController) = 0;

	virtual bool IsBaseController() = 0;
	virtual FName GetIdentifier() = 0;
};
