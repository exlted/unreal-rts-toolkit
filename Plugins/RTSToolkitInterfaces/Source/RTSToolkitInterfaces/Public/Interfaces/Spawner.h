// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Spawner.generated.h"

// This class does not need to be modified.
UINTERFACE()
class RTSTOOLKITINTERFACES_API USpawner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSTOOLKITINTERFACES_API ISpawner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SpawnEntity(UObject* WorldContext, FDataTableRowHandle EntityInfo, FTransform SpawnTransform) = 0;
	virtual void SpawnPlayerDefinedEntity(UObject* WorldContext, FDataTableRowHandle EntityInfo) = 0;
	virtual void FinishPlayerDefinedEntity(UObject* WorldContext, bool AddMultiple) = 0;
	virtual void CancelPlayerDefinedEntity() = 0;
	virtual TWeakObjectPtr<AActor> GetPlayerDefinedEntity() = 0;
};
