// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/DamageSources.h"
#include "UObject/Interface.h"
#include "Damagable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSUNITSYSTEM_API UDamagable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSUNITSYSTEM_API IDamagable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool IsDamagableBy(EDamageSource Source) = 0;
	// returns true when dealt damage kills
	virtual bool DoDamage(float Amount) = 0;
	
};
