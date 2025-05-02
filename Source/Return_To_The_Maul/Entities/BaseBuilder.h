// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "Return_To_The_Maul/Interfaces/Builder.h"
#include "BaseBuilder.generated.h"

UCLASS()
class RETURN_TO_THE_MAUL_API ABaseBuilder : public ABaseUnit, public IBuilder
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
