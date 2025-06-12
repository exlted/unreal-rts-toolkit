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
		for (const auto [Entity, SpawnOffset, Stats] : InitialEntities)
		{
			const auto UnitInfo = Entity.GetRow<FUnitInfo>("RequestedToBuild");
			const FTransform SpawnTransform = SpawnLocation + SpawnOffset;
			
			UAIBlueprintHelperLibrary::SpawnAIFromClass(WorldContext, UnitInfo->Class, nullptr,
				SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), true,
				SpawnOwner);
		}
	}
};