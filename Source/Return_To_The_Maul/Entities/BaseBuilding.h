// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "BaseBuilding.generated.h"

UCLASS()
class RETURN_TO_THE_MAUL_API ABaseBuilding : public ABaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
