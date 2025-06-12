#pragma once

#include "CoreMinimal.h"
#include "ResourceCost.generated.h"

USTRUCT(BlueprintType)
struct FResourceCost
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(GetOptions="EconomySettings.GetResourceTypes"))
	FName Resource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Cost;
};