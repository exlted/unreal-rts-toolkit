﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DebugResourceAdder.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETURN_TO_THE_MAUL_API UDebugResourceAdder : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDebugResourceAdder();
	

	FTimerHandle SpawnTimer;
	FTimerDelegate SpawnDelegate;

	UFUNCTION()
	void AddGold();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
