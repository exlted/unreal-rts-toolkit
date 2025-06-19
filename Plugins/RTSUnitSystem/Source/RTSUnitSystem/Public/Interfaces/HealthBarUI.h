// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/StatUpdater.h"
#include "UObject/Interface.h"
#include "HealthBarUI.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class RTSUNITSYSTEM_API UHealthBarUI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API IHealthBarUI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RegisterStatUpdater(const TScriptInterface<IStatUpdater>& StatUpdater);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeregisterStatUpdater(const TScriptInterface<IStatUpdater>& StatUpdater);
};
