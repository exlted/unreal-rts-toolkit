// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WaypointNode.h"

#include "Interfaces/WaypointFollower.h"
#include "Utils/ActorUtils.h"


// Sets default values
AWaypointNode::AWaypointNode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWaypointNode::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionMesh == nullptr)
	{
		CollisionMesh = GetRelatedSingletonTypedComponents<UPrimitiveComponent>(this);
	}
	
	if (CollisionMesh != nullptr)
	{
		CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AWaypointNode::OverlapBegin);
	}
}

// Called every frame
void AWaypointNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AWaypointNode::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto Follower = GetSingletonInterface<IWaypointFollower, UWaypointFollower>(OtherActor);
		Follower != nullptr && Follower->GetCurrentTarget() == this)
	{
		if (const auto Node = NextNode.Pin(); Node.IsValid())
		{
			Follower->SetNewTarget(Node.Get());
		}
	}
}

