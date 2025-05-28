// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseHomingBullet.h"
#include "Components/ActorComponent.h"
#include "Interfaces/TurretController.h"
#include "Interfaces/TurretWeapon.h"
#include "Weapon.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UWeapon : public UActorComponent, public ITurretWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
	TSubclassOf<ABaseHomingBullet> BulletClass;
	
	UPROPERTY(EditAnywhere)
	TScriptInterface<ITurretController> Controller;

	UPROPERTY(EditAnywhere)
	float WeaponTimeout = 5.0f;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
	// From Turret Controller
	virtual void FireAtTarget(AActor* Target) override;
	// From Bullet
	virtual void TargetKilled() override;
};
