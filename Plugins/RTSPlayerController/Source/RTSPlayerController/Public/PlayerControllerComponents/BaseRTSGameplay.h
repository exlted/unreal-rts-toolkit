// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/EControlStyle.h"
#include "Interfaces/HasSide.h"
#include "Interfaces/MoveUnit.h"
#include "Interfaces/PlayerControllerComponent.h"
#include "Interfaces/RTSCamera.h"
#include "Interfaces/RTSCursor.h"
#include "Interfaces/SelectUnit.h"
#include "BaseRTSGameplay.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSPLAYERCONTROLLER_API UBaseRTSGameplay : public UActorComponent, public IPlayerControllerComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseRTSGameplay();

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
	UInputAction* AddModifierAction;

	bool AddModifierPressed = false;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TScriptInterface<IHasSide> HasSide;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool Enabled;
	APlayerController* PlayerController;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Enable() override;
	virtual void Disable() override;

	virtual void SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
		UEnhancedInputComponent* EnhancedInputComponent, APlayerController* Controller) override;

	
	virtual bool IsBaseController() override;
	virtual FName GetIdentifier() override;
	
	virtual void OnInputStarted();
	virtual void OnPanTriggered(const FInputActionInstance& Instance);
	virtual void OnZoomTriggered(const FInputActionInstance& Instance);
	virtual void OnRotateTriggered(const FInputActionInstance& Instance);
	virtual void OnAddModifierTriggered(const FInputActionInstance& Instance);
	virtual void OnClickTriggered();
	virtual void OnMoveClickTriggered();
	
	// Utility Functions
	void PanScreen(const FVector& PanRate) const;
	void UpdateControlStyle(EControlStyle NewStyle);
};
