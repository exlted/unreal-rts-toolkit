// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugPlayerController.h"

#include "BasePlayerState.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/RTSCursor.h"

UDebugPlayerController::UDebugPlayerController()
{
}

void UDebugPlayerController::SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
	UEnhancedInputComponent* EnhancedInputComponent, APlayerController* Controller)
{
	Super::SetupInputComponent(Subsystem, EnhancedInputComponent, Controller);
	
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(DebugAction, ETriggerEvent::Started, this, &UDebugPlayerController::OnDebugTriggered);
	}
}

void UDebugPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void UDebugPlayerController::OnDebugTriggered(const FInputActionInstance& Instance)
{
	if (DebugClassToSpawn != nullptr && RTSCursor != nullptr)
	{
		if (const auto State = PlayerController->GetPlayerState<ABasePlayerState>(); State != nullptr)
		{
			auto CursorLocation = RTSCursor->GetCursorLocation();
			CursorLocation.Z += 20;
			
			State->UnitSpawningSystem->SpawnEntity(this, DebugClassToSpawn, FTransform(CursorLocation));
		}
	}
}
