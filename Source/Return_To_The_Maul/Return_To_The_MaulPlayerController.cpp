// Copyright Epic Games, Inc. All Rights Reserved.

#include "Return_To_The_MaulPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Return_To_The_MaulCharacter.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AReturn_To_The_MaulPlayerController::AReturn_To_The_MaulPlayerController():
  SpeedMult(1),
  PanZonePercent(10),
  PanCurve(nullptr),
  DefaultMappingContext(nullptr),
  ScrollAction(nullptr),
  MyCharacter(nullptr),
  ZoomPercent(1),
  Rotation(0)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AReturn_To_The_MaulPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AReturn_To_The_MaulPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	MouseControlPlayerTick(DeltaTime);
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
	
	if (!MyCharacter)
	{
		LazyLoadReferences();
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

	if (!MyCharacter)
	{
		LazyLoadReferences();
	}
	MyCharacter->UpdateSpringArmRotation(Rotation);
}

void AReturn_To_The_MaulPlayerController::MouseControlPlayerTick(float DeltaTime) const
{
	if (double x, y; GetMousePosition(x, y))
	{
		int32 ScreenWidth = 0, ScreenHeight = 0;
		GetViewportSize(ScreenWidth, ScreenHeight);

		const float XPanZone = ScreenWidth * PanZonePercent / 100;
		const float YPanZone = ScreenHeight * PanZonePercent / 100;

		FVector PanRate = FVector::ZeroVector;
		
		if (x < XPanZone)
		{
			PanRate.X = -1 * PanCurve->GetFloatValue(RatioBetween(XPanZone, 0, x));
		}
		else if (x > ScreenWidth - XPanZone)
		{
			PanRate.X = 1 * PanCurve->GetFloatValue(RatioBetween(ScreenWidth - XPanZone, ScreenWidth, x));
		}
		if (y < YPanZone)
		{
			PanRate.Y = 1 * PanCurve->GetFloatValue(RatioBetween(YPanZone, 0, y));
		}
		else if (y > ScreenHeight - YPanZone)
		{
			PanRate.Y = -1 * PanCurve->GetFloatValue(RatioBetween(ScreenHeight - YPanZone, ScreenHeight, y));
		}
		
		if (PanRate != FVector::ZeroVector)
		{
			PanScreen(PanRate);
		}
	}
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

void AReturn_To_The_MaulPlayerController::LazyLoadReferences()
{
	if (APawn* ControlledPawn = GetPawn(); ControlledPawn != nullptr && ControlledPawn->IsA<AReturn_To_The_MaulCharacter>())
	{
		MyCharacter = dynamic_cast<AReturn_To_The_MaulCharacter*>(ControlledPawn);
	}
}
