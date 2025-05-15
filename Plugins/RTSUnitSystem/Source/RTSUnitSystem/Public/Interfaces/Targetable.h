// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/FSide.h"
#include "UObject/Interface.h"
#include "Targetable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSUNITSYSTEM_API UTargetable : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSideChanged, FSide, UpdatedSide);

/**
 * 
 */
class RTSUNITSYSTEM_API ITargetable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FSide GetSide() = 0;
	
	template <class UserClass>
	void RegisterSideUpdatesInternal(UserClass* UserObject, void(UserClass::*Function)(FSide), FName FunctionName)
	{
		GetEventDelegate().__Internal_AddDynamic(UserObject, Function, FunctionName);
	}

#define RegisterSideUpdates(UserObject, FuncName) RegisterSideUpdatesInternal(UserObject, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) ))
	
	template <class UserClass>
	void DeregisterSideUpdatesInternal(UserClass* UserObject, void(UserClass::*Function)(FSide), FName FunctionName)
	{
		GetEventDelegate().__Internal_RemoveDynamic(UserObject, Function, FunctionName);
	}

#define DeregisterSideUpdates(UserObject, FuncName) DeregisterSideUpdatesInternal(UserObject, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) ))
	
private:
	virtual FSideChanged& GetEventDelegate() = 0;
};
