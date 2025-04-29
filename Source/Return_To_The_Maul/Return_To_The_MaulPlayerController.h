// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "Curves/CurveFloat.h"
#include "Return_To_The_MaulPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AReturn_To_The_MaulPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AReturn_To_The_MaulPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float SpeedMult;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float PanZonePercent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UCurveFloat* PanCurve;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Standard Camera Movement Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ScrollAction;
	
protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnScrollTriggered(const FInputActionInstance& Instance);

	void MouseControlPlayerTick(float DeltaTime) const;

	// Utility Functions
	void PanScreen(const FVector& PanRate) const;
	static float RatioBetween(float Start, float End, float Position);
	
private:
};


