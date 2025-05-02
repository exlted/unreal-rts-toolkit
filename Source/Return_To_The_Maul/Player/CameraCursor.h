// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraCursor.generated.h"

class USpringArmComponent;

UCLASS(Blueprintable)
class ACameraCursor : public APawn
{
	GENERATED_BODY()

public:
	enum class ECursorSpace
	{
		WorldSpace,
		ScreenSpace
	};
	
	ACameraCursor();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Cursor)
	float HeightAboveSurface = 10.0;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void PostInitializeComponents() override;

	void UpdateSpringArmTargetDistance(float NewTarget);
	void UpdateSpringArmPitch(float NewPitch);
	void UpdateSpringArmRotation(float NewRotation);

	void MoveCursorToWorldPosition(const FVector& MousePosition, const FVector& MouseDirection);
	void ResetCursorPosition();
	
	float GetHeightBeneathCursor(const FVector& CursorWorldPosition);
	float GetClosestToScreenAtPosition(const FVector& TracePosition);

	ECursorSpace SwapCursor();
	ECursorSpace GetCursorSpace();

private:
	USpringArmComponent* SpringArm;
	UStaticMeshComponent* WorldCursor;

	ECursorSpace CursorSpace = ECursorSpace::WorldSpace;
};

