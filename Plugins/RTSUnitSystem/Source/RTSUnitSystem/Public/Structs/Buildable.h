#pragma once
#include "Buildable.generated.h"

USTRUCT(BlueprintType)
struct FBuildable
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;
};
