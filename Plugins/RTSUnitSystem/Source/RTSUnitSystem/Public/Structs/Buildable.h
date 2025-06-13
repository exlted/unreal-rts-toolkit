#pragma once
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
