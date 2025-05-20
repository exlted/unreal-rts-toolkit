// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerComponents/BaseRTSGameplay.h"

#include "EnhancedInputComponent.h"
#include "Enums/EControlStyle.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/HasSide.h"
#include "Interfaces/MoveUnit.h"
#include "Interfaces/RTSCamera.h"
#include "Interfaces/RTSCursor.h"
#include "Interfaces/SelectUnit.h"
#include "Utils/ComponentUtils.h"
#include "Utils/Math.h"

// Sets default values for this component's properties
UBaseRTSGameplay::UBaseRTSGameplay()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseRTSGameplay::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (!PlayerController)
	{
		return;
	}
	
	if (PlayerController->IsLocalPlayerController())
	{
		APawn* ControlledPawn = PlayerController->GetPawn();
		if (!RTSCamera && ControlledPawn != nullptr && ControlledPawn->Implements<URTSCamera>())
		{
			RTSCamera = TScriptInterface<IRTSCamera>(ControlledPawn);
		}
		if (!RTSCursor && ControlledPawn != nullptr && ControlledPawn->Implements<URTSCursor>())
		{
			RTSCursor = TScriptInterface<IRTSCursor>(ControlledPawn);
		}
		
		const auto State = PlayerController->GetPlayerState<APlayerState>();
		if (State && !MoveUnit)
		{
			MoveUnit = GetRelatedSingletonComponent<IMoveUnit, UMoveUnit>(State);
		}
		if (State && !SelectUnit)
		{
			SelectUnit = GetRelatedSingletonComponent<ISelectUnit, USelectUnit>(State);
		}
		if (State && State->Implements<UHasSide>())
		{
			HasSide = TScriptInterface<IHasSide>(State);
		}
	}
}


// Called every frame
void UBaseRTSGameplay::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (!PlayerController || !Enabled)
	{
		return;
	}
	
	// Mouse Panning Code
	if (CurrentStyle == EControlStyle::MouseKeyboard)
	{
		if(const ULocalPlayer* LocPlayer = PlayerController->GetLocalPlayer(); LocPlayer && LocPlayer->ViewportClient )
		{
			if (LocPlayer->ViewportClient->Viewport->HasFocus())
			{
				if (FVector MousePosition; PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
				{
					if (RTSCursor != nullptr)
					{
						if (FVector WorldPosition, WorldDirection; PlayerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldPosition, WorldDirection))
						{
							RTSCursor->MoveCursorToCameraRelativePosition(WorldPosition, WorldDirection);
						}
					}
					
					int32 ScreenWidth = 0, ScreenHeight = 0;
					PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
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
			if (FVector WorldPosition, WorldDirection; PlayerController->DeprojectMousePositionToWorld( WorldPosition, WorldDirection))
			{
				RTSCursor->MoveCursorToCameraRelativePosition(WorldPosition, WorldDirection);
			}
		}
	}
}

void UBaseRTSGameplay::Enable()
{
	Enabled = true;
}

void UBaseRTSGameplay::Disable()
{
	Enabled = false;
}

void UBaseRTSGameplay::SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
UEnhancedInputComponent* EnhancedInputComponent, APlayerController* Controller)
{
	PlayerController = Controller;
	
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Started, this, &UBaseRTSGameplay::OnInputStarted);
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &UBaseRTSGameplay::OnPanTriggered);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Started, this, &UBaseRTSGameplay::OnInputStarted);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &UBaseRTSGameplay::OnZoomTriggered);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Started, this, &UBaseRTSGameplay::OnInputStarted);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &UBaseRTSGameplay::OnRotateTriggered);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &UBaseRTSGameplay::OnInputStarted);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &UBaseRTSGameplay::OnClickTriggered);
		EnhancedInputComponent->BindAction(MoveClickAction, ETriggerEvent::Started, this, &UBaseRTSGameplay::OnInputStarted);
		EnhancedInputComponent->BindAction(MoveClickAction, ETriggerEvent::Triggered, this, &UBaseRTSGameplay::OnMoveClickTriggered);
		EnhancedInputComponent->BindAction(AddModifierAction, ETriggerEvent::Triggered, this, &UBaseRTSGameplay::OnAddModifierTriggered);
	}
}

bool UBaseRTSGameplay::IsBaseController()
{
	return true;
}

FName UBaseRTSGameplay::GetIdentifier()
{
	return FName(TEXT("BaseController"));
}

void UBaseRTSGameplay::OnInputStarted()
{
	if (!PlayerController)
	{
		return;
	}
	
	if (const UInputDeviceSubsystem* InputDeviceSubsystem = GEngine->GetEngineSubsystem<UInputDeviceSubsystem>())
	{
		const FPlatformUserId UserId = PlayerController->GetPlatformUserId();
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

void UBaseRTSGameplay::OnPanTriggered(const FInputActionInstance& Instance)
{
	PanScreen(Instance.GetValue().Get<FVector>());
}

void UBaseRTSGameplay::OnZoomTriggered(const FInputActionInstance& Instance)
{
	if (RTSCamera != nullptr)
	{
		RTSCamera->ZoomCamera(ZoomSpeed * Instance.GetValue().Get<float>());
	}
}

void UBaseRTSGameplay::OnRotateTriggered(const FInputActionInstance& Instance)
{
	if (RTSCamera != nullptr)
	{
		RTSCamera->RotateCamera(Instance.GetValue().Get<float>());
	}
}

void UBaseRTSGameplay::OnAddModifierTriggered(const FInputActionInstance& Instance)
{
	const auto Test = Instance.GetValue();
	const auto Test2 = Test.Get<bool>();
	AddModifierPressed = Test2;
	if (AddModifierPressed)
	{
		OnInputStarted();
	}
}

void UBaseRTSGameplay::OnClickTriggered()
{
	if (!PlayerController)
	{
		return;
	}
	
	if (SelectUnit != nullptr && HasSide != nullptr)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Pawn, true, HitResult);
		
		SelectUnit->SelectUnit(HitResult.GetActor(), AddModifierPressed ? ESelectStyle::Add : ESelectStyle::New, HasSide->GetSide().Team);
	}
	else
	{
		if (const auto State = PlayerController->GetPlayerState<APlayerState>(); State != nullptr)
		{
			if (!SelectUnit)
			{
				SelectUnit = GetRelatedSingletonComponent<ISelectUnit, USelectUnit>(State);
			}
			if (State->Implements<UHasSide>())
			{
				HasSide = State;
			}
			// Intentional Re-entry
			OnClickTriggered();
		}
	}
}

void UBaseRTSGameplay::OnMoveClickTriggered()
{
	if (!PlayerController)
	{
		return;
	}
	
	if (MoveUnit != nullptr && RTSCursor != nullptr && HasSide != nullptr)
	{
		MoveUnit->MoveSelectedUnit(RTSCursor->GetCursorLocation(), HasSide->GetSide().Team);
	}
	else
	{
		if (const auto State = PlayerController->GetPlayerState<APlayerState>(); State != nullptr)
		{
			if (!MoveUnit)
			{
				MoveUnit = GetRelatedSingletonComponent<IMoveUnit, UMoveUnit>(State);
			}
			if (State->Implements<UHasSide>())
			{
				HasSide = State;
			}
			// Intentional Re-entry
			OnMoveClickTriggered();
		}
	}
}

void UBaseRTSGameplay::PanScreen(const FVector& PanRate) const
{
	if (!PlayerController)
	{
		return;
	}
	
	if (APawn* ControlledPawn = PlayerController->GetPawn(); ControlledPawn != nullptr && RTSCamera != nullptr)
	{
		const auto YawOnlyRotator = FRotator(0, RTSCamera->GetRotation(), 0);
		ControlledPawn->AddMovementInput(YawOnlyRotator.Quaternion().GetForwardVector(), PanRate.Y * PanSpeed, false);
		ControlledPawn->AddMovementInput(YawOnlyRotator.Quaternion().GetRightVector(), PanRate.X * PanSpeed, false);
	}
}

void UBaseRTSGameplay::UpdateControlStyle(const EControlStyle NewStyle)
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
			if (!PlayerController)
			{
				break;
			}
			
			int Width, Height;
			PlayerController->GetViewportSize(Width, Height);
			PlayerController->SetMouseLocation(Width / 2, Height / 2);
			break;
		case EControlStyle::Touch:
			break;
		}
	}
}

