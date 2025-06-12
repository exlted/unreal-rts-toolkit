#pragma once
#include "Objects/ResourceCost.h"
#include "Structs/UnitInfo.h"
#include "Buildable.generated.h"

USTRUCT(BlueprintType)
struct FBuildable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RowType=UnitInfo))
	FDataTableRowHandle UnitInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerDefinedLocation;
};
