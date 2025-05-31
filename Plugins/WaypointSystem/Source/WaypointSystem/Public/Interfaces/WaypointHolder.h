// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WaypointHolder.generated.h"

// This class does not need to be modified.
UINTERFACE()
class WAYPOINTSYSTEM_API UWaypointHolder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WAYPOINTSYSTEM_API IWaypointHolder
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TArray<FVector> GetPath() = 0;
};
