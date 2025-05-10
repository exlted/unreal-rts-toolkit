// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/FSide.h"
#include "UObject/Interface.h"
#include "HasSide.generated.h"

// This class does not need to be modified.
UINTERFACE()
class SUPPORTFUNCTIONS_API UHasSide : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SUPPORTFUNCTIONS_API IHasSide
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FSide GetSide() = 0;
};
