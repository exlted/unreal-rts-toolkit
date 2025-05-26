// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Targetable.h"
#include "UObject/Interface.h"
#include "TurretWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSUNITSYSTEM_API UTurretWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API ITurretWeapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// From Turret Controller
	virtual void FireAtTarget(TScriptInterface<ITargetable> Target) = 0;
	// From Bullet
	virtual void TargetKilled() = 0;
};
