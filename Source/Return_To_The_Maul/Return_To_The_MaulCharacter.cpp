// Copyright Epic Games, Inc. All Rights Reserved.

#include "Return_To_The_MaulCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AReturn_To_The_MaulCharacter::AReturn_To_The_MaulCharacter()
{
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AReturn_To_The_MaulCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AReturn_To_The_MaulCharacter::UpdateSpringArmTargetDistance(float NewTarget)
{
	if (auto SpringArm = GetComponentByClass<USpringArmComponent>(); SpringArm != nullptr)
	{
		SpringArm->TargetArmLength = NewTarget;
	}
}
