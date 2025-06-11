// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/Buildable.h"
#include "Builder.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class RTSUNITSYSTEM_API UBuilder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API IBuilder
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TArray<FBuildable> GetBuildableObjects() = 0;
	virtual void DisplayUI() = 0;
	virtual void HideUI() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnMenuItemClicked(const FBuildable& RequestedItem);

	virtual void OnMenuItemClicked_Implementation(const FBuildable& RequestedItem)
	{
		UE_LOG(LogTemp, Error, TEXT("OnMenuItemClicked Called Without Overriding Function"));
	}
};
