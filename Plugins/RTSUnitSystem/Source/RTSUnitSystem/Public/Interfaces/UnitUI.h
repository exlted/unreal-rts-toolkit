// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/StatUpdater.h"
#include "UObject/Interface.h"
#include "UnitUI.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class RTSUNITSYSTEM_API UUnitUI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API  IUnitUI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddUnit(FDataTableRowHandle UnitInfo, const TScriptInterface<IStatUpdater>& StatCallback);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddUnitNoStats(FDataTableRowHandle UnitInfo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveUnit(FDataTableRowHandle UnitInfo, const TScriptInterface<IStatUpdater>& StatCallback);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClearUnits();
};
