// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/FSide.h"
#include "UnitSpawningSystem.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UUnitSpawningSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUnitSpawningSystem();

protected:
	// Needs an FSide
	FSide Side;
	 
public:

	virtual void SpawnEntity(UObject* WorldContext, UClass* SpawnClass, FTransform SpawnTransform);
	virtual void SetSide(FSide NewSide);

	// Server Functions
	UFUNCTION(Server, Reliable)
	virtual void ServerSpawnEntity(UObject* WorldContext, UClass* SpawnClass, FTransform SpawnTransform);
};
