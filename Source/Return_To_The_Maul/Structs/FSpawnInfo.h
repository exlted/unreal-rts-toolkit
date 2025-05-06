#pragma once

#include "CoreMinimal.h"
#include "FSpawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnInfo, meta=(AllowPrivateAccess = "true",
		AllowedClasses="/Script/Return_To_The_Maul.BaseUnit, /Script/Return_To_The_Maul.BaseBuilding, /Script/Return_To_The_Maul.BaseTerrain"))
	UClass* Entity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnInfo, meta=(AllowPrivateAccess = "true"))
	FTransform SpawnOffset;
};