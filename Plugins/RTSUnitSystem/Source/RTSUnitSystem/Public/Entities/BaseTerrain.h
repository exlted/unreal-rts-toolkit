// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "BaseTerrain.generated.h"

UCLASS()
class RTSUNITSYSTEM_API ABaseTerrain : public ABaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseTerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
