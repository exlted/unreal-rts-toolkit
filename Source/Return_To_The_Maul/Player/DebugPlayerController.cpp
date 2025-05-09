// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugPlayerController.h"

#include "BasePlayerState.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/RTSCursor.h"

ADebugPlayerController::ADebugPlayerController()
{
}

void ADebugPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(DebugAction, ETriggerEvent::Triggered, this, &ADebugPlayerController::OnDebugTriggered);
	}
}

void ADebugPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ADebugPlayerController::OnDebugTriggered(const FInputActionInstance& Instance)
{
	if (DebugClassToSpawn != nullptr && RTSCursor != nullptr)
	{
		if (const auto State = GetPlayerState<ABasePlayerState>(); PlayerState != nullptr)
		{
			auto CursorLocation = RTSCursor->GetCursorLocation();
			CursorLocation.Z += 20;
			
			State->UnitSpawningSystem->SpawnEntity(this, DebugClassToSpawn, FTransform(CursorLocation));
		}
	}
}
