#pragma once

#include "CoreMinimal.h"
#include "FSpawnInfo.h"
#include "FFactionInfo.generated.h"

USTRUCT(BlueprintType)
struct FFactionInfo2
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	TArray<FSpawnInfo> InitialEntities;
	
	void SpawnInitialEntities(UWorld& World, const FTransform& SpawnLocation)
	{
		for (const auto [Entity, SpawnOffset] : InitialEntities)
		{
			const FTransform SpawnTransform = SpawnLocation + SpawnOffset;
			World.SpawnActor(Entity, &SpawnTransform);
		}
	}
};