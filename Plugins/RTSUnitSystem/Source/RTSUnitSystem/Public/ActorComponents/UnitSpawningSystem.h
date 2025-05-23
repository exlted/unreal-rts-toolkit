// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ghosted.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Spawner.h"
#include "Structs/FSide.h"
#include "UnitSpawningSystem.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UUnitSpawningSystem : public UActorComponent, public ISpawner
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUnitSpawningSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
	TSubclassOf<UGhosted> GhostedSubclass;
	
protected:
	// Needs an FSide
	FSide Side;
	AActor* PlayerSpawnedActor;
	 
public:

	virtual void SpawnEntity(UObject* WorldContext, UClass* SpawnClass, FTransform SpawnTransform) override;
	virtual void SpawnPlayerDefinedEntity(UObject* WorldContext, UClass* SpawnClass) override;
	virtual void FinishPlayerDefinedEntity(UObject* WorldContext, bool AddMultiple) override;
	virtual void CancelPlayerDefinedEntity() override;
	virtual TWeakObjectPtr<AActor> GetPlayerDefinedEntity() override;
	
	virtual void SetSide(FSide NewSide);

	// Server Functions
	UFUNCTION(Server, Reliable)
	virtual void ServerSpawnEntity(UObject* WorldContext, UClass* SpawnClass, FTransform SpawnTransform);
};
