// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Turret.h"

#include "Interfaces/TurretWeapon.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UTurret::UTurret()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurret::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Weapon = GetRelatedSingletonComponent<ITurretWeapon, UTurretWeapon>(GetOwner());
}


// Called every frame
void UTurret::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (Timeout <= 0.0f)
	{
		if (Fired == false)
		{
			if (ValidTargets.Num() > 0 && Weapon != nullptr)
			{
				Fired = true;
				Weapon->FireAtTarget(ValidTargets[0]);
			}
		}
	}
	else if (Timeout > 0.0f)
	{
		Timeout -= DeltaTime;
	}
}

void UTurret::SetCurrentTargetsInRange(TArray<AActor*> Targets)
{
	ValidTargets = Targets;
}

void UTurret::SetWeaponTimeout(float NewTimeout)
{
	Timeout = NewTimeout;
	Fired = false;
}

void UTurret::TargetKilled()
{
}

void UTurret::BlockAction()
{
	Fired = true;
}

