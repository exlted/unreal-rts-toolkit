// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/UIManager.h"
#include "UObject/Interface.h"
#include "HasUIManager.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIMANAGER_API UHasUIManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UIMANAGER_API IHasUIManager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TWeakObjectPtr<UUIManager> GetUIManager() = 0;
};
