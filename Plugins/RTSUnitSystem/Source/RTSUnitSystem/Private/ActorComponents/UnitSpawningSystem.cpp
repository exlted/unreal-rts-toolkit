// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/UnitSpawningSystem.h"

#include "ActorComponents/Ghosted.h"
#include "ActorComponents/TeamColorizer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Utils/ComponentUtils.h"
#include "Interfaces/Spawnable.h"
#include "Interfaces/TurretController.h"


// Sets default values for this component's properties
UUnitSpawningSystem::UUnitSpawningSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UUnitSpawningSystem::SpawnEntity(UObject* WorldContext, UClass* SpawnClass, const FTransform SpawnTransform)
{
	ServerSpawnEntity(WorldContext, SpawnClass, SpawnTransform);
}
void UUnitSpawningSystem::SpawnPlayerDefinedEntity(UObject* WorldContext, UClass* SpawnClass)
{
	const auto GhostedClass = GhostedSubclass.Get();
	if (GhostedClass != nullptr)
	{
		PlayerSpawnedActor = WorldContext->GetWorld()->SpawnActor(SpawnClass);
		if (PlayerSpawnedActor != nullptr)
		{
			for (const auto Colorizers = GetRelatedTypedComponents<UTeamColorizer>(PlayerSpawnedActor);
				 const auto& Colorizer : Colorizers)
			{
				Colorizer->Disable();
			}
			if (const auto Turret = GetRelatedSingletonComponent<ITurretController, UTurretController>(PlayerSpawnedActor);
				Turret != nullptr)
			{
				Turret->BlockAction();
			}
			PlayerSpawnedActor->AddComponentByClass(GhostedClass, false, FTransform::Identity, false);
		}
	}
}

void UUnitSpawningSystem::FinishPlayerDefinedEntity(UObject* WorldContext, const bool AddMultiple)
{
	if (PlayerSpawnedActor != nullptr)
	{
		ServerSpawnEntity(WorldContext, PlayerSpawnedActor->GetClass(), PlayerSpawnedActor->GetTransform());

		if (!AddMultiple)
		{
			PlayerSpawnedActor->Destroy();
			PlayerSpawnedActor = nullptr;
		}
	}
}

void UUnitSpawningSystem::CancelPlayerDefinedEntity()
{
	if (PlayerSpawnedActor)
	{
		PlayerSpawnedActor->Destroy();
		PlayerSpawnedActor = nullptr;
	}
}

TWeakObjectPtr<AActor> UUnitSpawningSystem::GetPlayerDefinedEntity()
{
	return PlayerSpawnedActor;
}

void UUnitSpawningSystem::SetSide(FSide NewSide)
{
	Side = NewSide;
}

void UUnitSpawningSystem::ServerSpawnEntity_Implementation(UObject* WorldContext, UClass* SpawnClass,
	FTransform SpawnTransform)
{
	const auto Pawn = UAIBlueprintHelperLibrary::SpawnAIFromClass(WorldContext, SpawnClass, nullptr,
		SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), true,
		GetOwner());

	if (const auto Spawnable = GetRelatedSingletonComponent<ISpawnable, USpawnable>(Pawn); Spawnable != nullptr)
	{
		Spawnable->SetSide(Side);
	}
}

