// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Structs/FSelected.h"
#include "BasePlayerController.generated.h"

class IMoveUnit;
class ISelectUnit;
struct FInputActionInstance;
enum class EControlStyle;
class IRTSCursor;
class IRTSCamera;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class RTSPLAYERCONTROLLER_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float PanSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float PanZonePercent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UCurveFloat* PanCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ZoomSpeed;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Standard Camera Pan Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ScrollAction;
	
	/** Standard Camera Zoom Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;
	
	/** Standard Camera Rotate Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* RotateAction;
	
	/** Standard Camera Rotate Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TScriptInterface<IRTSCamera> RTSCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TScriptInterface<IRTSCursor> RTSCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	EControlStyle CurrentStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TScriptInterface<ISelectUnit> SelectUnit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TScriptInterface<IMoveUnit> MoveUnit;

	
	
protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

	/** Input handlers for SetDestination action. */
	virtual void OnInputStarted();
	virtual void OnPanTriggered(const FInputActionInstance& Instance);
	virtual void OnZoomTriggered(const FInputActionInstance& Instance);
	virtual void OnRotateTriggered(const FInputActionInstance& Instance);
	virtual void OnClickTriggered();
	virtual void OnMoveClickTriggered();
	
	// Utility Functions
	void PanScreen(const FVector& PanRate) const;
	void UpdateControlStyle(EControlStyle NewStyle);

	// Server Functions
	//UFUNCTION(Server, Reliable)
	//void MoveOrder(const TArray<FSelected>& Actors, const FVector& NewLocation);
	
};
