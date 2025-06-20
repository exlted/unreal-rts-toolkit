﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/TurretController.h"
#include "Turret.generated.h"


class ITurretWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UTurret : public UActorComponent, public ITurretController
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTurret();

	UPROPERTY(EditAnywhere)
	TScriptInterface<ITurretWeapon> Weapon;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ValidTargets;

	UPROPERTY(EditAnywhere)
	float Timeout = -1;

	UPROPERTY(EditAnywhere)
	bool Fired = false;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
	// From Turret Collider
	virtual void SetCurrentTargetsInRange(TArray<AActor*> Targets) override;

	// From Turret Weapon
	virtual void SetWeaponTimeout(float NewTimeout) override;
	virtual void TargetKilled() override;

	virtual void BlockAction() override;
};
