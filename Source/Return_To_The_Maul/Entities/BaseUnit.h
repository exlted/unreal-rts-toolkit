// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Return_To_The_Maul/Interfaces/Movable.h"
#include "Return_To_The_Maul/Interfaces/Selectable.h"
#include "Return_To_The_Maul/Interfaces/Targetable.h"
#include "BaseUnit.generated.h"

UCLASS()
class RETURN_TO_THE_MAUL_API ABaseUnit : public ACharacter, public ISelectable, public IMovable, public ITargetable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
