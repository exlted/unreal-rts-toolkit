#pragma once

#include "CoreMinimal.h"
#include "FSpawnInfo.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "FFactionInfo.generated.h"

USTRUCT(BlueprintType)
struct FFactionInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	TArray<FSpawnInfo> InitialEntities;
	
	void SpawnInitialEntities(UObject* WorldContext, const FTransform& SpawnLocation, AActor* SpawnOwner)
	{
		for (const auto [Entity, SpawnOffset] : InitialEntities)
		{
			const FTransform SpawnTransform = SpawnLocation + SpawnOffset;
			//World.SpawnActor(Entity, &SpawnTransform);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(WorldContext, Entity, nullptr,
				SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), true,
				SpawnOwner);
		}
	}
};