// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/AutoSpawner.h"
#include "CreepSpawner.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UCreepSpawner : public UActorComponent, public IAutoSpawner
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCreepSpawner();

	UPROPERTY(EditAnywhere)
	TArray<FWave> Waves;
	int CurrentWave = -1;
	int CreepIndex = INT_MAX;

	float MinSpawnTime;
	float MaxSpawnTime;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle SpawnTimer;
	FTimerDelegate SpawnDelegate;

	UFUNCTION()
	void SpawnCreep();

	void ScheduleNextSpawn();
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void SpawnNextWave() override;
	virtual bool HasAnotherWave() override;
	virtual const FWave& GetNextWave() override;
};
