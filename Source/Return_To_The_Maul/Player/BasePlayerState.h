// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "../Structs/FFactionInfo.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true"))
	FColor UnitColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true"))
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true"))
	FName PlayerTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true"))
	FFactionInfo2 Faction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Side, meta=(AllowPrivateAccess = "true", AllowedClasses="FactionInfo"))
	int Team;
};
