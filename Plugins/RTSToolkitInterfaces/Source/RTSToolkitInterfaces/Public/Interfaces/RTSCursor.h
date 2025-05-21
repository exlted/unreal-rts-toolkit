// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/ECursorMode.h"
#include "RTSCursor.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSTOOLKITINTERFACES_API URTSCursor : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */
class RTSTOOLKITINTERFACES_API IRTSCursor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ChangeCursorVisibility(bool NewVisibilityState) = 0;
	virtual bool GetCursorVisibility() const = 0;

	virtual void ChangeCursorMode(ECursorMode NewCursorMode) = 0;
	virtual ECursorMode GetCursorMode() const = 0;
	
	virtual void MoveCursorToCameraRelativePosition(const FVector& MousePosition, const FVector& MouseDirection) const = 0;
	virtual void MoveCursorTo(const FVector& WorldSpaceCoordinates) const = 0;
	virtual void MoveCursorTo(const FVector2D& ScreenSpaceCoordinates) const = 0;
	virtual void ResetCursorPosition() const = 0;
	virtual FVector GetCursorLocation() const = 0;
	virtual FVector2D GetCursorScreenLocation() const = 0;
};
