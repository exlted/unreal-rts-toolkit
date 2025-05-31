// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/CreepSpawner.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/GameController.h"
#include "Interfaces/Movable.h"
#include "Interfaces/Spawnable.h"
#include "Interfaces/Spawner.h"
#include "Interfaces/WaypointHolder.h"
#include "Utils/ActorUtils.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UCreepSpawner::UCreepSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCreepSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnDelegate.BindUFunction(this, FName("SpawnCreep"));
	if (const auto GameMode = GetWorld()->GetAuthGameMode();
		GameMode != nullptr)
	{
		if (GameMode->Implements<UGameController>())
		{
			const auto GameController = TScriptInterface<IGameController>(GameMode);
			GameController->RegisterSpawner(this);
		}
	}
}


void UCreepSpawner::SpawnCreep()
{
	CreepIndex++;

	// Spawn the requested creep with the requested stats
	const auto ToSpawn = Waves[CurrentWave].CreepsToSpawn[CreepIndex];
	
	FTransform SpawnTransform = GetOwner()->GetActorTransform();
	SpawnTransform += ToSpawn.SpawnOffset;
	
	const auto Pawn = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetOwner(), ToSpawn.Entity, nullptr,
		SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), true,
		GetOwner());

	//if (const auto Spawnable = GetRelatedSingletonComponent<ISpawnable, USpawnable>(Pawn); Spawnable != nullptr)
	//{
	//	Spawnable->SetSide(Side);
	//}
	
	if (const auto Movable = GetRelatedSingletonComponent<IMovable, UMovable>(Pawn);
		Movable != nullptr)
	{
		// Get Waypoint Path, Tell Movable to follow Waypoint Path
		if (const auto WaypointHolder = GetRelatedSingletonComponent<IWaypointHolder, UWaypointHolder>(GetOwner());
			WaypointHolder != nullptr)
		{
			// TODO: Use the whole path, and not just the first node
			Movable->MoveTo(WaypointHolder->GetPath()[0]);
		}
	}
	
	if (CreepIndex + 1 < Waves[CurrentWave].CreepsToSpawn.Num())
	{
		ScheduleNextSpawn();
	}
}

void UCreepSpawner::ScheduleNextSpawn()
{
	GetOwner()->GetWorldTimerManager().SetTimer(SpawnTimer, SpawnDelegate, FMath::RandRange(MinSpawnTime, MaxSpawnTime), false);
}

// Called every frame
void UCreepSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCreepSpawner::SpawnNextWave()
{
	CurrentWave++;
	CreepIndex = -1;
	// Inverted because the "Minimum" creeps per second would have the longest period between creeps, and vice versa
	MaxSpawnTime = 1.0f / Waves[CurrentWave].MinCreepsPerSecond;
	MinSpawnTime = 1.0f / Waves[CurrentWave].MaxCreepsPerSecond;

	ScheduleNextSpawn();
}

bool UCreepSpawner::HasAnotherWave()
{
	return CurrentWave + 1 < Waves.Num();
}

const FWave& UCreepSpawner::GetNextWave()
{
	return Waves[CurrentWave + 1];
}

