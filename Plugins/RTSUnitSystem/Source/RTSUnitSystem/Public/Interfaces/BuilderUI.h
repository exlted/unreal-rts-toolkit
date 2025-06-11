// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/Buildable.h"
#include "UObject/Interface.h"
#include "BuilderUI.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class RTSUNITSYSTEM_API UBuilderUI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API IBuilderUI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddBuildableItems(const TArray<FBuildable>& NewItems, const TScriptInterface<IBuilder>& AssociatedBuilder);

	void AddBuildableItems_Implementation(const TArray<FBuildable>& NewItems, const TScriptInterface<IBuilder>& AssociatedBuilder)
	{
		UE_LOG(LogTemp, Display, TEXT("AddBuildableItems called without being overridden"));
	}
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClearBuildableItems();

	void ClearBuildableItems_Implementation()
	{
		UE_LOG(LogTemp, Display, TEXT("ClearBuildableItems called without being overridden"));
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateAvailableResources(const FResourceData& UpdatedResourceData);

	void UpdateAvailableResources_Implementation(const FResourceData& UpdatedResourceData)
	{
		UE_LOG(LogTemp, Display, TEXT("UpdateAvailableResources called without being overridden"));
	}
};