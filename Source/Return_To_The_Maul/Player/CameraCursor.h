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

	void UpdateSpringArmTargetDistance(float NewTarget) const;
	void UpdateSpringArmPitch(float NewPitch) const;
	void UpdateSpringArmRotation(float NewRotation) const;
	
	void MoveCursorToWorldPosition(const FVector& MousePosition, const FVector& MouseDirection) const;
	void ResetCursorPosition() const;
	
	float GetHeightBeneathCursor(const FVector& CursorWorldPosition) const;
	float GetClosestToScreenAtPosition(const FVector& TracePosition) const;
	
	FVector GetCursorLocation() const;

	ECursorSpace SwapCursor();
	ECursorSpace GetCursorSpace();

private:
	USpringArmComponent* SpringArm;
	UStaticMeshComponent* WorldCursor;

	ECursorSpace CursorSpace = ECursorSpace::WorldSpace;
};

