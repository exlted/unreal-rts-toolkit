// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PauseMenu.generated.h"

// This class does not need to be modified.
UINTERFACE()
class SIMPLEMENUSYSTEM_API UPauseMenu : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLEMENUSYSTEM_API IPauseMenu
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HidePauseMenu();
};
