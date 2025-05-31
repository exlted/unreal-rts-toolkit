// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugPlayerController.h"

#include "BasePlayerState.h"
#include "EnhancedInputComponent.h"

UDebugPlayerController::UDebugPlayerController()
{
}

void UDebugPlayerController::Enable()
{
}

void UDebugPlayerController::Disable()
{
}

void UDebugPlayerController::SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
                                                 UEnhancedInputComponent* EnhancedInputComponent, APlayerController* Controller)
{
	if (Subsystem)
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}
	
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(DebugAction, ETriggerEvent::Triggered, this, &UDebugPlayerController::OnDebugTriggered);
	}
	
	PlayerController = Controller;
}

bool UDebugPlayerController::IsBaseController()
{
		return true;
}

FName UDebugPlayerController::GetIdentifier()
{
	return FName("Debug");
}

void UDebugPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void UDebugPlayerController::OnDebugTriggered(const FInputActionInstance& Instance)
{
	if (const auto State = PlayerController->GetPlayerState<ABasePlayerState>(); State != nullptr)
	{
		State->StartNextWave();
	}
}
