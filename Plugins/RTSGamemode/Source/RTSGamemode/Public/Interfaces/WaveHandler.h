// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveVoteHandler.h"
#include "UObject/Interface.h"
#include "WaveHandler.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FNextWaveParameter, const TArray<FDataTableRowHandle>&, WaveInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNextWave, const TArray<FDataTableRowHandle>&, WaveInfo);

// This class does not need to be modified.
UINTERFACE()
class RTSGAMEMODE_API UWaveHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSGAMEMODE_API IWaveHandler
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RegisterWaveDataCallback(const FNextWaveParameter& Callback);
	virtual void RegisterWaveDataCallback_Implementation(const FNextWaveParameter& Callback) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnregisterWaveDataCallback(const FNextWaveParameter& Callback);
	virtual void UnregisterWaveDataCallback_Implementation(const FNextWaveParameter& Callback) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitializeNextWaveData(const FNextWaveParameter& Callback);
	virtual void InitializeNextWaveData_Implementation(const FNextWaveParameter& Callback) = 0;
};
