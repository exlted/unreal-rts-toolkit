// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Return_To_The_MaulCharacter.generated.h"

UCLASS(Blueprintable)
class AReturn_To_The_MaulCharacter : public APawn
{
	GENERATED_BODY()

public:
	AReturn_To_The_MaulCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	void UpdateSpringArmTargetDistance(float NewTarget);
	void UpdateSpringArmPitch(float NewPitch);
	void UpdateSpringArmRotation(float NewRotation);
};

