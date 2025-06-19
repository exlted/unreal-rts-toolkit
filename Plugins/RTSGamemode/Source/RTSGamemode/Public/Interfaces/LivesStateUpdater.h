// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LivesStateUpdater.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FLivesChangedParameter, int, NewLifeCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLivesChanged, int, NewLifeCount);

// This class does not need to be modified.
UINTERFACE()
class RTSGAMEMODE_API ULivesStateUpdater : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSGAMEMODE_API ILivesStateUpdater
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RegisterLivesChanged(const FLivesChangedParameter& CallbackFunc);
	virtual void RegisterLivesChanged_Implementation(const FLivesChangedParameter& CallbackFunc)
	{
		UE_LOG(LogTemp, Display, TEXT("RegisterLivesChanged Called Without Being Overridden"));
	}
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnregisterLivesChanged(const FLivesChangedParameter& CallbackFunc);
	virtual void UnregisterLivesChanged_Implementation(const FLivesChangedParameter& CallbackFunc)
	{
		UE_LOG(LogTemp, Display, TEXT("RegisterLivesChanged Called Without Being Overridden"));
	}
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitializeLivesState(const FLivesChangedParameter& CallbackFunc);
	virtual void InitializeLivesState_Implementation(const FLivesChangedParameter& CallbackFunc)
	{
		UE_LOG(LogTemp, Display, TEXT("RegisterLivesChanged Called Without Being Overridden"));
	}
};
