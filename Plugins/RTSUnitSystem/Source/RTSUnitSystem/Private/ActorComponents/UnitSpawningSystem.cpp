// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/UnitSpawningSystem.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Interfaces/Spawnable.h"


// Sets default values for this component's properties
UUnitSpawningSystem::UUnitSpawningSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

APawn* UUnitSpawningSystem::SpawnEntity(UObject* WorldContext, UClass* SpawnClass, const FTransform SpawnTransform)
{
	const auto Pawn = UAIBlueprintHelperLibrary::SpawnAIFromClass(WorldContext, SpawnClass, nullptr,
		SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), true,
		GetOwner());

	if (Pawn->Implements<USpawnable>())
	{
		const auto Spawnable = TScriptInterface<ISpawnable>(Pawn);
		Spawnable->SetSide(Side);
	}

	return Pawn;
}

void UUnitSpawningSystem::SetSide(const FSide NewSide)
{
	Side = NewSide;
}

