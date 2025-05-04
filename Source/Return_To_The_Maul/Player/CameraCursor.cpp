// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraCursor.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Return_To_The_Maul/Utils/Trace.h"

ACameraCursor::ACameraCursor()
  : SpringArm(nullptr)
  , WorldCursor(nullptr)
{
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACameraCursor::Tick(const float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ACameraCursor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpringArm = GetComponentByClass<USpringArmComponent>();
	
	for (const auto Cursors = GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("Cursor")); const auto Actor : Cursors)
	{
		if (const auto TypedCursor = dynamic_cast<UStaticMeshComponent*>(Actor))
		{
			if (TypedCursor->ComponentHasTag(TEXT("World")))
			{
				WorldCursor = TypedCursor;
			}
		}
	}
}

void ACameraCursor::UpdateSpringArmTargetDistance(const float NewTarget) const
{
	SpringArm->TargetArmLength = NewTarget;
}

void ACameraCursor::UpdateSpringArmPitch(const float NewPitch) const
{
	auto Rotation = SpringArm->GetRelativeRotation();
	Rotation.Pitch = NewPitch;
		
	SpringArm->SetRelativeRotation(Rotation);
}

void ACameraCursor::UpdateSpringArmRotation(const float NewRotation) const
{
	auto Rotation = SpringArm->GetRelativeRotation();
	Rotation.Yaw = NewRotation;
		
	SpringArm->SetRelativeRotation(Rotation);
}

void ACameraCursor::MoveCursorToWorldPosition(const FVector& MousePosition, const FVector& MouseDirection) const
{
	const auto RootPosition = this->GetActorLocation();


	// Maybe use a raytrace to determine final middle location? Slow?
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	const FHitResult RV_Hit = DoSingleLineTrace(
		this,
		FLineSegment(MousePosition, MouseDirection, 10000.0f),
		ECC_WorldStatic,
		RV_TraceParams);

	if (RV_Hit.bBlockingHit)
	{
		const FVector EndLocation = RV_Hit.ImpactPoint;
		const FVector FilteredPosition = FVector(EndLocation.X - RootPosition.X, EndLocation.Y - RootPosition.Y, GetHeightBeneathCursor(EndLocation) - RootPosition.Z);
			
		WorldCursor->SetRelativeLocation(FilteredPosition);
	}
	else
	{
		// If there isn't an intersection on the Trace, Place it on the RootPosition
		const FVector EndLocation = FMath::LinePlaneIntersection(
					   MousePosition,
					   MousePosition + (MouseDirection * 10000.0f),
					   RootPosition,
					   FVector{0.f, 0.f, 1.f});
		
		const FVector FilteredPosition = FVector(EndLocation.X - RootPosition.X, EndLocation.Y - RootPosition.Y,
			GetHeightBeneathCursor(EndLocation) - RootPosition.Z);
			
		WorldCursor->SetRelativeLocation(FilteredPosition);
	}
}

void ACameraCursor::ResetCursorPosition() const
{
	WorldCursor->SetRelativeLocation(FVector(0, 0, WorldCursor->GetRelativeLocation().Z));
}

float ACameraCursor::GetHeightBeneathCursor(const FVector& CursorWorldPosition) const
{
	return GetClosestToScreenAtPosition(CursorWorldPosition) + HeightAboveSurface;
}

float ACameraCursor::GetClosestToScreenAtPosition(const FVector& TracePosition) const
{
	const auto PlayerController = GetLocalViewingPlayerController();

	FVector2D ScreenPosition;
	PlayerController->ProjectWorldLocationToScreen(TracePosition, ScreenPosition);
	FVector WorldLocation;
	FVector WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldLocation, WorldDirection);

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	const FHitResult RV_Hit = DoSingleLineTrace(
		this,
		FLineSegment(WorldLocation, WorldDirection, 10000.0f),
		ECC_WorldStatic,
		RV_TraceParams);

	if (RV_Hit.bBlockingHit)
	{
		return RV_Hit.ImpactPoint.Z;
	}

	// If we didn't hit anything, we're probably in the void, so treat as if we hit at 0
	return 0;
}

FVector ACameraCursor::GetCursorLocation() const
{
	return WorldCursor->GetRelativeLocation() + GetActorLocation();
}

ACameraCursor::ECursorSpace ACameraCursor::SwapCursor()
{
	switch (CursorSpace)
	{
	case ECursorSpace::WorldSpace:
		CursorSpace = ECursorSpace::ScreenSpace;

		// Do Work to Swap Cursor
		
		break;
	case ECursorSpace::ScreenSpace:
		CursorSpace = ECursorSpace::WorldSpace;

		// Do Work to Swap Cursor
		
		break;
	}

	return CursorSpace;
}

ACameraCursor::ECursorSpace ACameraCursor::GetCursorSpace() const
{
	return CursorSpace;
}
