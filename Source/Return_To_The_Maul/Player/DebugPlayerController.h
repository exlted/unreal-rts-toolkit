// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "DebugPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API ADebugPlayerController : public ABasePlayerController
{
	GENERATED_BODY()
public:
	ADebugPlayerController();
	
	/** Standard Camera Pan Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DebugAction;
	
protected:
	virtual void SetupInputComponent() override;
	
	virtual void OnDebugTriggered(const FInputActionInstance& Instance);
};
