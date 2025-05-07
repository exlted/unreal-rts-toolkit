// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Structs/FSide.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FSide Side;
};
