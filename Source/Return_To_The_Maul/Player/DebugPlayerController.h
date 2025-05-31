// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerComponents/BaseRTSGameplay.h"
#include "DebugPlayerController.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETURN_TO_THE_MAUL_API UDebugPlayerController : public UActorComponent, public IPlayerControllerComponent
{
	GENERATED_BODY()
public:
	UDebugPlayerController();
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;
	
	/** Standard Camera Pan Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DebugAction;

	virtual void Enable() override;
	virtual void Disable() override;

	virtual void SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
		UEnhancedInputComponent* EnhancedInputComponent, APlayerController* PlayerController) override;

	virtual bool IsBaseController() override;
	virtual FName GetIdentifier() override;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void OnDebugTriggered(const FInputActionInstance& Instance);

	
	APlayerController* PlayerController;
};
