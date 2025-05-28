// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Weapon.h"

#include "Chaos/CollisionResolutionUtil.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeapon::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Controller = GetRelatedSingletonComponent<ITurretController, UTurretController>(GetOwner());
}


// Called every frame
void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeapon::FireAtTarget(AActor* Target)
{
	// Spawn Bullet at Us with Target
	const auto Transform = GetOwner()->GetTransform();
	const auto Bullet = Cast<ABaseHomingBullet>(GetWorld()->SpawnActor(BulletClass.Get(), &Transform));
	Bullet->Target = Target;
	Bullet->Weapon = this;
	Bullet->Ready = true;
	
	if (Controller)
	{
		Controller->SetWeaponTimeout(WeaponTimeout);
	}
}

void UWeapon::TargetKilled()
{
	if (Controller)
	{
		Controller->TargetKilled();
	}
}

