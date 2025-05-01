// Copyright Epic Games, Inc. All Rights Reserved.

#include "Return_To_The_MaulPlayerController.h"

#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Return_To_The_MaulCharacter.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AReturn_To_The_MaulPlayerController::AReturn_To_The_MaulPlayerController():
	SpeedMult(1),
	PanZonePercent(10),
	PanCurve(nullptr),
	DefaultMappingContext(nullptr),
	ScrollAction(nullptr),
	ZoomCurve(nullptr),
	PitchCurve(nullptr),
	ZoomAction(nullptr),
	RotateAction(nullptr),
	UserInputPosition(nullptr),
	MyCharacter(nullptr),
	ZoomPercent(1),
	Rotation(0),
	CurrentStyle()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AReturn_To_The_MaulPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	if (APawn* ControlledPawn = GetPawn(); ControlledPawn != nullptr && ControlledPawn->IsA<AReturn_To_The_MaulCharacter>())
	{
		MyCharacter = dynamic_cast<AReturn_To_The_MaulCharacter*>(ControlledPawn);
	}
}

void AReturn_To_The_MaulPlayerController::PlayerTick(const float DeltaTime)
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
					if (MyCharacter->GetCursorSpace() == AReturn_To_The_MaulCharacter::ECursorSpace::WorldSpace)
					{
						if (FVector WorldPosition, WorldDirection; DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldPosition, WorldDirection))
						{
							MyCharacter->MoveCursorToWorldPosition(WorldPosition, WorldDirection);
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
		if (MyCharacter->GetCursorSpace() == AReturn_To_The_MaulCharacter::ECursorSpace::WorldSpace)
		{
			if (FVector WorldPosition, WorldDirection; DeprojectMousePositionToWorld( WorldPosition, WorldDirection))
			{
				MyCharacter->MoveCursorToWorldPosition(WorldPosition, WorldDirection);
			}
		}
	}
}

void AReturn_To_The_MaulPlayerController::SetupInputComponent()
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
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Started, this, &AReturn_To_The_MaulPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &AReturn_To_The_MaulPlayerController::OnPanTriggered);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AReturn_To_The_MaulPlayerController::OnZoomTriggered);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AReturn_To_The_MaulPlayerController::OnRotateTriggered);
		EnhancedInputComponent->BindAction(UserInputPosition, ETriggerEvent::Triggered, this, &AReturn_To_The_MaulPlayerController::OnPositionTriggered);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AReturn_To_The_MaulPlayerController::OnInputStarted()
{
	StopMovement();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AReturn_To_The_MaulPlayerController::OnPanTriggered(const FInputActionInstance& Instance)
{
	PanScreen(Instance.GetValue().Get<FVector>());
}

void AReturn_To_The_MaulPlayerController::OnZoomTriggered(const FInputActionInstance& Instance)
{
	ZoomPercent += .01 * Instance.GetValue().Get<float>();
	if (ZoomPercent > 1)
	{
		ZoomPercent = 1;
	}
	else if (ZoomPercent < 0)
	{
		ZoomPercent = 0;
	}
	
	MyCharacter->UpdateSpringArmTargetDistance(ZoomCurve->GetFloatValue(ZoomPercent));
	MyCharacter->UpdateSpringArmPitch(PitchCurve->GetFloatValue(ZoomPercent));
}

void AReturn_To_The_MaulPlayerController::OnRotateTriggered(const FInputActionInstance& Instance)
{
	Rotation += Instance.GetValue().Get<float>();
	if (ZoomPercent > 365)
	{
		ZoomPercent -= 365;
	}
	else if (ZoomPercent < 0)
	{
		ZoomPercent += 365;
	}

	MyCharacter->UpdateSpringArmRotation(Rotation);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AReturn_To_The_MaulPlayerController::OnPositionTriggered(const FInputActionInstance& Instance)
{
	// Implement switch to Mouse mode here?
}

void AReturn_To_The_MaulPlayerController::PanScreen(const FVector& PanRate) const
{
	if (APawn* ControlledPawn = GetPawn(); ControlledPawn != nullptr)
	{
		const auto YawOnlyRotator = FRotator(0, Rotation, 0);
		
		ControlledPawn->AddMovementInput(YawOnlyRotator.Quaternion().GetForwardVector(), PanRate.Y * SpeedMult, false);
		ControlledPawn->AddMovementInput(YawOnlyRotator.Quaternion().GetRightVector(), PanRate.X * SpeedMult, false);
	}
}

float AReturn_To_The_MaulPlayerController::RatioBetween(const float Start, const float End, const float Position)
{
	return fabs(End - Position) / fabs(End - Start);
}

void AReturn_To_The_MaulPlayerController::UpdateControlStyle(const EControlStyle NewStyle)
{
	if (NewStyle != CurrentStyle)
	{
		CurrentStyle = NewStyle;
		switch (CurrentStyle)
		{
		case EControlStyle::MouseKeyboard:
			break;
		case EControlStyle::Gamepad:
			MyCharacter->ResetCursorPosition();
			int Width, Height;
			GetViewportSize(Width, Height);
			SetMouseLocation(Width / 2, Height / 2);
			break;
		}
	}
}
