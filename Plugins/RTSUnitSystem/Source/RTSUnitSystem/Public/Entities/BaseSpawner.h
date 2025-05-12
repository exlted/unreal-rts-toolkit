﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuilding.h"
#include "Interfaces/Builder.h"
#include "BaseSpawner.generated.h"

UCLASS()
class RTSUNITSYSTEM_API ABaseSpawner : public ABaseBuilding
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
