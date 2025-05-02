// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Return_To_The_Maul/Interfaces/Selectable.h"
#include "Return_To_The_Maul/Interfaces/Targetable.h"
#include "BaseActor.generated.h"

UCLASS()
class RETURN_TO_THE_MAUL_API ABaseActor : public AActor, public ISelectable, public ITargetable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
