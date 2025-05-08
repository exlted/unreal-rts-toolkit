// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugPlayerController.h"

#include "EnhancedInputComponent.h"

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

void ADebugPlayerController::OnDebugTriggered(const FInputActionInstance& Instance)
{
	
}
