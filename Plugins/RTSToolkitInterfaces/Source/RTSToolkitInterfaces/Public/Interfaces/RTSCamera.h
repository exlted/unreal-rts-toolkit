// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSCamera.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSTOOLKITINTERFACES_API URTSCamera : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSTOOLKITINTERFACES_API IRTSCamera
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ZoomCamera(float Amount) = 0;
	virtual void ZoomCameraAbsolute(float NewZoom) = 0;
	virtual float GetZoom() = 0;
	
	virtual void RotateCamera(float Amount) = 0;
	virtual void RotateCameraAbsolute(float NewRotation) = 0;
	virtual float GetRotation() = 0;
};
