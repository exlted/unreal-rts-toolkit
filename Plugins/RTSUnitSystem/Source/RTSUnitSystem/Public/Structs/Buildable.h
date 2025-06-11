#pragma once
#include "Structs/ResourceCost.h"
#include "Buildable.generated.h"

USTRUCT(BlueprintType)
struct FBuildable
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerDefinedLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceCost> BuildCost;
};
