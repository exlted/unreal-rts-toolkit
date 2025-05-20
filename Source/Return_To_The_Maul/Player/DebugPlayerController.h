// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "PlayerControllerComponents/BaseRTSGameplay.h"
#include "DebugPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API UDebugPlayerController : public UBaseRTSGameplay
{
	GENERATED_BODY()
public:
	UDebugPlayerController();
	
	/** Standard Camera Pan Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DebugAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UClass* DebugClassToSpawn;

	FTransform SpawnTransform;
	
protected:
	virtual void SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
		UEnhancedInputComponent* EnhancedInputComponent, APlayerController* Controller) override;

	virtual void BeginPlay() override;
	
	virtual void OnDebugTriggered(const FInputActionInstance& Instance);
};
