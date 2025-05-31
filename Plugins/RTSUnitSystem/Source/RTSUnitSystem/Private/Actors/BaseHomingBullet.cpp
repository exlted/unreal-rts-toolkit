// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseHomingBullet.h"

#include "Interfaces/Damagable.h"
#include "Utils/ComponentUtils.h"


// Sets default values
ABaseHomingBullet::ABaseHomingBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseHomingBullet::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionMesh == nullptr)
	{
		CollisionMesh = GetRelatedSingletonTypedComponents<UPrimitiveComponent>(this);
	}
	
	if (CollisionMesh != nullptr)
	{
		CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseHomingBullet::OverlapBegin);
	}
}

// Called every frame
void ABaseHomingBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Ready)
	{
		if (!Target.IsValid())
		{
			Destroy();
			return;
		}

		const auto Actor = Target.Pin();
		
		const auto TargetLocation = Actor->GetActorLocation();
		const auto MyLocation = GetActorLocation();

		auto MyDirection = TargetLocation - MyLocation;
		MyDirection = MyDirection / MyDirection.Length();

		SetActorLocation(MyLocation + (MyDirection * Speed), true, nullptr);
	}
}

void ABaseHomingBullet::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If the overlapped actor is damageable, deal damage to them and delete
	if (const auto Actor = Target.Pin();
		Actor != nullptr && OtherActor == Actor.Get())
	{
		if (const auto Damagable = GetRelatedSingletonComponent<IDamagable, UDamagable>(OtherActor);
			Damagable != nullptr)
		{
			if (Damagable->DoDamage(this->Damage))
			{
				Weapon->TargetKilled();
			}
		}
		
		Destroy();
	}
}

