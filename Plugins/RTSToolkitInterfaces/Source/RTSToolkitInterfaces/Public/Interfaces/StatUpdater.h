// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Templates/Tuple.h"
#include "StatUpdater.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class RTSTOOLKITINTERFACES_API UStatUpdater : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStatUpdatedParameter, FName, Name, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStatUpdated, FName, Name, float, Value);
/**
 * 
 */
class RTSTOOLKITINTERFACES_API IStatUpdater
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RegisterStatUpdatedCallback(const FStatUpdatedParameter& CallbackFunc);
	
	virtual void RegisterStatUpdatedCallback_Implementation(const FStatUpdatedParameter& CallbackFunc)
	{
		UE_LOG(LogTemp, Error, TEXT("RegisterStatUpdatedCallback Called Without Overriding Function"));
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeregisterStatUpdatedCallback(const FStatUpdatedParameter& CallbackFunc);
	
	virtual void DeregisterStatUpdatedCallback_Implementation(const FStatUpdatedParameter& CallbackFunc)
	{
		UE_LOG(LogTemp, Error, TEXT("DeregisterStatUpdatedCallback Called Without Overriding Function"));
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitializeCurrentState(const FStatUpdatedParameter& CallbackFunc);
	
	virtual void InitializeCurrentState_Implementation(const FStatUpdatedParameter& CallbackFunc)
	{
		UE_LOG(LogTemp, Error, TEXT("InitializeCurrentState Called Without Overriding Function"));
	}
};
