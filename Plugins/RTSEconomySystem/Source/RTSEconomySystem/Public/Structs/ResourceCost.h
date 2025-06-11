#pragma once

#include "CoreMinimal.h"
#include "ResourceCost.generated.h"

USTRUCT(BlueprintType)
struct FResourceCost
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Resource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Cost;
};