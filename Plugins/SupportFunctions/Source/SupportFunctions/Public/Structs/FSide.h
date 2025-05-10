#pragma once

#include "CoreMinimal.h"
#include "Structs/FFactionInfo.h"
#include "FSide.generated.h"


USTRUCT(BlueprintType)
struct FSide
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true"))
	FColor UnitColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true"))
	FName PlayerTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true"))
	FFactionInfo Faction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true"))
	int Team;
};
