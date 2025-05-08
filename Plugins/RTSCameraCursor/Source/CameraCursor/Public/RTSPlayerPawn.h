// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enums/ECursorMode.h"
#include "Interfaces/RTSCamera.h"
#include "Interfaces/RTSCursor.h"
#include "RTSPlayerPawn.generated.h"

class UMovementComponent;
class UImage;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CAMERACURSOR_API ARTSPlayerPawn : public APawn, public IRTSCursor, public IRTSCamera
{
	GENERATED_BODY()

public:
	
	// Sets default values for this pawn's properties
	ARTSPlayerPawn();

	UPROPERTY(EditAnywhere, Category = Movement)
	UMovementComponent* MovementComponent;
	
	// CAMERA INFORMATION
	
	// Camera Components
	UPROPERTY(EditAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* Camera;

	// Value from 0 to 1, used to look up from ZoomCurve and PitchCurve
	UPROPERTY(EditAnywhere, Category = Camera)
	float ZoomLevel;
	
	// Maps from 0 to 1 the length of SpringArm
	UPROPERTY(EditAnywhere, Category = Camera)
	UCurveFloat* ZoomCurve;

	// Maps from 0 to 1 the pitch of SpringArm
	UPROPERTY(EditAnywhere, Category = Camera)
	UCurveFloat* PitchCurve;

	// CURSOR INFORMATION
	// Cursor Components
	// World Space Cursor
	UPROPERTY(EditAnywhere, Category = Cursor)
	UStaticMeshComponent* WorldCursor;
	
	UPROPERTY(EditAnywhere, Category = Cursor)
	bool Visible;
	
	UPROPERTY(EditAnywhere, Category = Cursor)
	ECursorMode CursorMode;
	
	// Height Above the "surface" that the WorldSpace Cursor should be
	UPROPERTY(EditAnywhere, Category = Cursor)
	float HeightAboveSurface = 10.0;

	// Pitch for the Camera to be at where we should automatically swap to a Screen-Space Cursor
	UPROPERTY(EditAnywhere, Category = Cursor)
	float SwapPitch = 30;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void ChangeCursorVisibility(bool NewVisibilityState) override;
	virtual bool GetCursorVisibility() const override;

	virtual void ChangeCursorMode(ECursorMode NewCursorMode) override;
	virtual ECursorMode GetCursorMode() const override;

	// Move BOTH Screen Space and World Space Cursors to the passed in location
	virtual void MoveCursorToCameraRelativePosition(const FVector& MousePosition, const FVector& MouseDirection) const override;
	virtual void MoveCursorTo(const FVector& WorldSpaceCoordinates) const override;
	virtual void MoveCursorTo(const FVector2D& ScreenSpaceCoordinates) const override;
	virtual void ResetCursorPosition() const override;
	virtual FVector GetCursorLocation() const override;
	virtual FVector2D GetCursorScreenLocation() const override;

	// Zoom is a 0 to 1 scale which is defined by the Zoom and Pitch Curves
	//   !!! These functions will affect BOTH Zoom and Pitch of the camera !!!
	virtual void ZoomCamera(float Amount) override;
	virtual void ZoomCameraAbsolute(float NewZoom) override;
	virtual float GetZoom() override;

	virtual void RotateCamera(float Amount) override;
	virtual void RotateCameraAbsolute(float NewRotation) override;
	virtual float GetRotation() override;
	
private:
	float GetClosestToScreenAtPosition(const FVector& TracePosition) const;
};
