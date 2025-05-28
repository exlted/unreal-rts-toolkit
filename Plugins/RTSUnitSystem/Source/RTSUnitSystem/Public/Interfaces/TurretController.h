// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Targetable.h"
#include "UObject/Interface.h"
#include "TurretController.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSUNITSYSTEM_API UTurretController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API ITurretController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// From Turret Collider
	virtual void SetCurrentTargetsInRange(TArray<AActor*> Targets) = 0;

	// From Turret Weapon
	virtual void SetWeaponTimeout(float Timeout) = 0;
	virtual void TargetKilled() = 0;

	// For Ghost Mode
	virtual void BlockAction() = 0;
};
