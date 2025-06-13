#pragma once

#include "CoreMinimal.h"
#include "Enums/EEntityType.h"
#include "Structs/ResourceCost.h"
#include "UnitInfo.generated.h"

USTRUCT(BlueprintType)
struct FUnitInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UClass* Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEntityType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FResourceCost> Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(GetKeyOptions="StatSettings.GetStatTypes"))
	TMap<FName, float> Stats;
};