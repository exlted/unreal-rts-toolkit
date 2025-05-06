// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTSPlayerController.h"

#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputSettings.h"
#include "../Utils/Math.h"
#include "Interfaces/RTSCamera.h"
#include "Interfaces/RTSCursor.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ARTSPlayerController::ARTSPlayerController()
:   SpeedMult(1)
,   PanZonePercent(10)
,   PanCurve(nullptr)
,   DefaultMappingContext(nullptr)
,   ScrollAction(nullptr)
,   ZoomAction(nullptr)
,   RotateAction(nullptr)
,   ClickAction(nullptr)
,   MoveClickAction(nullptr)
,   CurrentStyle()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ARTSPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr && ControlledPawn->Implements<URTSCamera>())
	{
		Camera = TScriptInterface<IRTSCamera>(ControlledPawn);
	}
	if (ControlledPawn != nullptr && ControlledPawn->Implements<URTSCursor>())
	{
		Cursor = TScriptInterface<IRTSCursor>(ControlledPawn);
	}
}

void ARTSPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

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
	}
	
	// Mouse Panning Code
	if (CurrentStyle == EControlStyle::MouseKeyboard)
	{
		if(const ULocalPlayer* LocPlayer = Cast<ULocalPlayer>(Player); LocPlayer && LocPlayer->ViewportClient )
		{
			if (LocPlayer->ViewportClient->Viewport->HasMouseCapture())
			{
				if (FVector MousePosition; GetMousePosition(MousePosition.X, MousePosition.Y))
				{
					if (Cursor != nullptr)
					{
						if (FVector WorldPosition, WorldDirection; DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldPosition, WorldDirection))
						{
							Cursor->MoveCursorToCameraRelativePosition(WorldPosition, WorldDirection);
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
		if (Cursor != nullptr)
		{
			if (FVector WorldPosition, WorldDirection; DeprojectMousePositionToWorld( WorldPosition, WorldDirection))
			{
				Cursor->MoveCursorToCameraRelativePosition(WorldPosition, WorldDirection);
			}
		}
	}
}

void ARTSPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Started, this, &ARTSPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &ARTSPlayerController::OnPanTriggered);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ARTSPlayerController::OnZoomTriggered);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ARTSPlayerController::OnRotateTriggered);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &ARTSPlayerController::OnClickTriggered);
		EnhancedInputComponent->BindAction(MoveClickAction, ETriggerEvent::Triggered, this, &ARTSPlayerController::OnMoveClickTriggered);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ARTSPlayerController::OnInputStarted()
{
	StopMovement();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ARTSPlayerController::OnPanTriggered(const FInputActionInstance& Instance)
{
	PanScreen(Instance.GetValue().Get<FVector>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ARTSPlayerController::OnZoomTriggered(const FInputActionInstance& Instance)
{
	if (Camera != nullptr)
	{
		Camera->ZoomCamera(0.1 * Instance.GetValue().Get<float>());
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ARTSPlayerController::OnRotateTriggered(const FInputActionInstance& Instance)
{
	if (Camera != nullptr)
	{
		Camera->RotateCamera(Instance.GetValue().Get<float>());
	}
}

void ARTSPlayerController::OnClickTriggered()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Pawn, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		SelectedCharacter.Select(HitResult.GetActor());
	}
	else
	{
		SelectedCharacter.Select(nullptr);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ARTSPlayerController::OnMoveClickTriggered()
{
	if (SelectedCharacter.CanMove() && Cursor != nullptr)
	{
		SelectedCharacter.MoveTo(Cursor->GetCursorLocation());
	}
}

void ARTSPlayerController::PanScreen(const FVector& PanRate) const
{
	if (APawn* ControlledPawn = GetPawn(); ControlledPawn != nullptr && Camera != nullptr)
	{
		const auto YawOnlyRotator = FRotator(0, Camera->GetRotation(), 0);
		
		ControlledPawn->AddMovementInput(YawOnlyRotator.Quaternion().GetForwardVector(), PanRate.Y * SpeedMult, false);
		ControlledPawn->AddMovementInput(YawOnlyRotator.Quaternion().GetRightVector(), PanRate.X * SpeedMult, false);
	}
}

void ARTSPlayerController::UpdateControlStyle(const EControlStyle NewStyle)
{
	if (NewStyle != CurrentStyle)
	{
		CurrentStyle = NewStyle;
		switch (CurrentStyle)
		{
		case EControlStyle::MouseKeyboard:
			break;
		case EControlStyle::Gamepad:
			if (Cursor != nullptr)
			{
				Cursor->ResetCursorPosition();
			}
			int Width, Height;
			GetViewportSize(Width, Height);
			SetMouseLocation(Width / 2, Height / 2);
			break;
		}
	}
}
