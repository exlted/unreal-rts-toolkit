// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WaypointFollower.generated.h"

// This class does not need to be modified.
UINTERFACE()
class WAYPOINTSYSTEM_API UWaypointFollower : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WAYPOINTSYSTEM_API IWaypointFollower
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual AActor* GetCurrentTarget() = 0;
	virtual void SetNewTarget(AActor* NewTarget) = 0;
};
