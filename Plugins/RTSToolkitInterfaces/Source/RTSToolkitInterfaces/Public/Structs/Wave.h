#pragma once

#include "CoreMinimal.h"
#include "Structs/FSpawnInfo.h"
#include "Wave.generated.h"

USTRUCT(BlueprintType)
struct FWave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSpawnInfo> CreepsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinCreepsPerSecond;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxCreepsPerSecond;
};