#pragma once

#include "CoreMinimal.h"
#include "FSpawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnInfo, meta=(AllowPrivateAccess = "true",
		AllowedClasses="/Script/RTSUnitSystem.BaseUnit, /Script/RTSUnitSystem.BaseBuilding, /Script/RTSUnitSystem.BaseTerrain"))
	UClass* Entity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnInfo, meta=(AllowPrivateAccess = "true"))
	FTransform SpawnOffset;
};