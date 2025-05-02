#pragma once

#include "CoreMinimal.h"
#include "FSpawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnInfo, meta=(AllowPrivateAccess = "true"))
	UClass* Entity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnInfo, meta=(AllowPrivateAccess = "true", AllowedClasses="BaseUnit, BaseBuilding"))
	FTransform SpawnOffset;
};