#pragma once

#include "CoreMinimal.h"
#include "UnitInfo.h"
#include "UnitStats.h"
#include "FSpawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnInfo, meta=(AllowPrivateAccess = "true", RowType=UnitInfo))
	FDataTableRowHandle EntityInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnInfo, meta=(AllowPrivateAccess = "true"))
	FTransform SpawnOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUnitStats Stats;
};