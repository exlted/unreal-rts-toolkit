// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Enums/EControlStyle.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/RTSCamera.h"
#include "Interfaces/RTSCursor.h"
#include "Interfaces/SelectUnit.h"
#include "Interfaces/MoveUnit.h"
#include "Utils/Math.h"

ABasePlayerController::ABasePlayerController()
	  : PanSpeed(100)
	  , PanZonePercent(10)
	  , PanCurve(nullptr)
	  , ZoomSpeed(.01f)
	  , DefaultMappingContext(nullptr)
	  , ScrollAction(nullptr)
	  , ZoomAction(nullptr)
	  , RotateAction(nullptr)
	  , ClickAction(nullptr)
	  , MoveClickAction(nullptr)
	  , CurrentStyle()
{
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Started, this, &ABasePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnPanTriggered);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Started, this, &ABasePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnZoomTriggered);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Started, this, &ABasePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnRotateTriggered);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &ABasePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnClickTriggered);
		EnhancedInputComponent->BindAction(MoveClickAction, ETriggerEvent::Started, this, &ABasePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(MoveClickAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnMoveClickTriggered);
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalPlayerController())
	{
		APawn* ControlledPawn = GetPawn();
		if (!RTSCamera && ControlledPawn != nullptr && ControlledPawn->Implements<URTSCamera>())
		{
			RTSCamera = TScriptInterface<IRTSCamera>(ControlledPawn);
		}
		if (!RTSCursor && ControlledPawn != nullptr && ControlledPawn->Implements<URTSCursor>())
		{
			RTSCursor = TScriptInterface<IRTSCursor>(ControlledPawn);
		}
		
		const auto State = GetPlayerState<APlayerState>();
		if (!MoveUnit && State != nullptr && State->Implements<UMoveUnit>())
		{
			MoveUnit = TScriptInterface<IMoveUnit>(State);
		}
		if (!SelectUnit && State != nullptr && State->Implements<USelectUnit>())
		{
			SelectUnit = TScriptInterface<ISelectUnit>(State);
		}
	}
}

void ABasePlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	
	// Mouse Panning Code
	if (CurrentStyle == EControlStyle::MouseKeyboard)
	{
		if(const ULocalPlayer* LocPlayer = Cast<ULocalPlayer>(Player); LocPlayer && LocPlayer->ViewportClient )
		{
			if (LocPlayer->ViewportClient->Viewport->HasMouseCapture())
			{
				if (FVector MousePosition; GetMousePosition(MousePosition.X, MousePosition.Y))
				{
					if (RTSCursor != nullptr)
					{
						if (FVector WorldPosition, WorldDirection; DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldPosition, WorldDirection))
						{
							RTSCursor->MoveCursorToCameraRelativePosition(WorldPosition, WorldDirection);
						}
					}
					
					int32 ScreenWidth = 0, ScreenHeight = 0;
					GetViewportSize(ScreenWidth, ScreenHeight);
					const float XPanZone = ScreenWidth * PanZonePercent / 100;
					const float YPanZone = ScreenHeight * PanZonePercent / 100;
					FVector PanRate = FVector::ZeroVector;
	
					if (MousePosition.X < XPanZone)
					{
						PanRate.X = -1 * PanCurve->GetFloatValue(RatioBetween(XPanZone, 0, MousePosition.X));
					}
					else if (MousePosition.X > ScreenWidth - XPanZone)
					{
						PanRate.X = 1 * PanCurve->GetFloatValue(RatioBetween(ScreenWidth - XPanZone, ScreenWidth, MousePosition.X));
					}
					if (MousePosition.Y < YPanZone)
					{
						PanRate.Y = 1 * PanCurve->GetFloatValue(RatioBetween(YPanZone, 0, MousePosition.Y));
					}
					else if (MousePosition.Y > ScreenHeight - YPanZone)
					{
						PanRate.Y = -1 * PanCurve->GetFloatValue(RatioBetween(ScreenHeight - YPanZone, ScreenHeight, MousePosition.Y));
					}
	
					if (PanRate != FVector::ZeroVector)
					{
						PanScreen(PanRate);
					}
				}
			}
		}
	}
	else
	{
		if (RTSCursor != nullptr)
		{
			if (FVector WorldPosition, WorldDirection; DeprojectMousePositionToWorld( WorldPosition, WorldDirection))
			{
				RTSCursor->MoveCursorToCameraRelativePosition(WorldPosition, WorldDirection);
			}
		}
	}
}

void ABasePlayerController::OnInputStarted()
{
	// TODO: Store InputDeviceSubsystem so we're not constantly looking it up
	if (const UInputDeviceSubsystem* InputDeviceSubsystem = GEngine->GetEngineSubsystem<UInputDeviceSubsystem>())
	{
		const FPlatformUserId UserId = GetPlatformUserId();
		if (const FHardwareDeviceIdentifier DeviceIdentifier = InputDeviceSubsystem->GetMostRecentlyUsedHardwareDevice(UserId);
			DeviceIdentifier.PrimaryDeviceType == EHardwareDevicePrimaryType::Gamepad)
		{
			UpdateControlStyle(EControlStyle::Gamepad);
		}
		else if (DeviceIdentifier.PrimaryDeviceType == EHardwareDevicePrimaryType::KeyboardAndMouse)
		{
			UpdateControlStyle(EControlStyle::MouseKeyboard);
		}
		else if (DeviceIdentifier.PrimaryDeviceType == EHardwareDevicePrimaryType::Touch)
		{
			UpdateControlStyle(EControlStyle::Touch);
		}
	}
}

void ABasePlayerController::OnPanTriggered(const FInputActionInstance& Instance)
{
	PanScreen(Instance.GetValue().Get<FVector>());
}

void ABasePlayerController::OnZoomTriggered(const FInputActionInstance& Instance)
{
	if (RTSCamera != nullptr)
	{
		RTSCamera->ZoomCamera(ZoomSpeed * Instance.GetValue().Get<float>());
	}
}

void ABasePlayerController::OnRotateTriggered(const FInputActionInstance& Instance)
{
	if (RTSCamera != nullptr)
	{
		RTSCamera->RotateCamera(Instance.GetValue().Get<float>());
	}
}

void ABasePlayerController::OnClickTriggered()
{
	if (SelectUnit != nullptr)
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Pawn, true, HitResult);
		
		SelectUnit->SelectUnit(HitResult.GetActor(), ESelectStyle::New);
	}
	else
	{
		if (const auto State = GetPlayerState<APlayerState>(); !SelectUnit && State != nullptr && State->Implements<UMoveUnit>())
		{
			SelectUnit = TScriptInterface<ISelectUnit>(State);
			// Intentional Re-entry
			OnClickTriggered();
		}
	}
}

void ABasePlayerController::OnMoveClickTriggered()
{
	if (MoveUnit != nullptr && RTSCursor != nullptr)
	{
		MoveUnit->MoveSelectedUnit(RTSCursor->GetCursorLocation());
	}
	else
	{
		if (const auto State = GetPlayerState<APlayerState>(); !MoveUnit && State != nullptr && State->Implements<UMoveUnit>())
		{
			MoveUnit = TScriptInterface<IMoveUnit>(State);
			// Intentional Re-entry
			OnMoveClickTriggered();
		}
	}
}

void ABasePlayerController::PanScreen(const FVector& PanRate) const
{
	if (APawn* ControlledPawn = GetPawn(); ControlledPawn != nullptr && RTSCamera != nullptr)
	{
		const auto YawOnlyRotator = FRotator(0, RTSCamera->GetRotation(), 0);
		ControlledPawn->AddMovementInput(YawOnlyRotator.Quaternion().GetForwardVector(), PanRate.Y * PanSpeed, false);
		ControlledPawn->AddMovementInput(YawOnlyRotator.Quaternion().GetRightVector(), PanRate.X * PanSpeed, false);
	}
}

void ABasePlayerController::UpdateControlStyle(const EControlStyle NewStyle)
{
	if (NewStyle != CurrentStyle)
	{
		CurrentStyle = NewStyle;
		switch (CurrentStyle)
		{
		case EControlStyle::MouseKeyboard:
			break;
		case EControlStyle::Gamepad:
			if (RTSCursor != nullptr)
			{
				RTSCursor->ResetCursorPosition();
			}
			int Width, Height;
			GetViewportSize(Width, Height);
			SetMouseLocation(Width / 2, Height / 2);
			break;
		case EControlStyle::Touch:
			break;
		}
	}
}
