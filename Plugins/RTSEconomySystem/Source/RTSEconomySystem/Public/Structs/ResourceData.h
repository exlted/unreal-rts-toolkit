#pragma once

#include "CoreMinimal.h"
#include "ResourceData.generated.h"

USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_BODY()

	// In Game Const
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShowMaxValue;

	// In Game Modifiable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Deleted;
};