// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Curves/CurveFloat.h"
#include "RTSPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;
class ACameraCursor;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	enum class EControlStyle
	{
		MouseKeyboard,
		Gamepad
	};
	
	ARTSPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float SpeedMult;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float PanZonePercent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UCurveFloat* PanCurve;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Standard Camera Pan Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ScrollAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UCurveFloat* ZoomCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UCurveFloat* PitchCurve;
	
	/** Standard Camera Zoom Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;
	
	/** Standard Camera Rotate Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* RotateAction;
	
	/** Standard Camera Rotate Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* UserInputPosition;
	
protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnPanTriggered(const FInputActionInstance& Instance);
	void OnZoomTriggered(const FInputActionInstance& Instance);
	void OnRotateTriggered(const FInputActionInstance& Instance);
	void OnPositionTriggered(const FInputActionInstance& Instance);
	
	// Utility Functions
	void PanScreen(const FVector& PanRate) const;
	static float RatioBetween(float Start, float End, float Position);
	void UpdateControlStyle(EControlStyle NewStyle);
	
private:
	ACameraCursor* MyCharacter;

	float ZoomPercent; // From 0 to 1
	float Rotation;
	EControlStyle CurrentStyle;
};


