// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraCursor.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"

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

void ACameraCursor::Tick(float DeltaSeconds)
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

void ACameraCursor::UpdateSpringArmTargetDistance(const float NewTarget)
{
	SpringArm->TargetArmLength = NewTarget;
}

void ACameraCursor::UpdateSpringArmPitch(const float NewPitch)
{
	auto Rotation = SpringArm->GetRelativeRotation();
	Rotation.Pitch = NewPitch;
		
	SpringArm->SetRelativeRotation(Rotation);
}

void ACameraCursor::UpdateSpringArmRotation(const float NewRotation)
{
	auto Rotation = SpringArm->GetRelativeRotation();
	Rotation.Yaw = NewRotation;
		
	SpringArm->SetRelativeRotation(Rotation);
}

void ACameraCursor::MoveCursorToWorldPosition(const FVector& MousePosition, const FVector& MouseDirection)
{
	const auto RootPosition = this->GetActorLocation();


	// Maybe use a raytrace to determine final middle location? Slow?
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);
	
	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByObjectType(
		RV_Hit,
		MousePosition,
		MousePosition + (MouseDirection * 10000.0f), 
		ECC_WorldStatic,
		RV_TraceParams
	);

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
		
		const FVector FilteredPosition = FVector(EndLocation.X - RootPosition.X, EndLocation.Y - RootPosition.Y, GetHeightBeneathCursor(EndLocation) - RootPosition.Z);
			
		WorldCursor->SetRelativeLocation(FilteredPosition);
	}
}

void ACameraCursor::ResetCursorPosition()
{
	WorldCursor->SetRelativeLocation(FVector(0, 0, WorldCursor->GetRelativeLocation().Z));
}

float ACameraCursor::GetHeightBeneathCursor(const FVector& CursorWorldPosition)
{
	FVector MinBounds;
	FVector MaxBounds;
	
	WorldCursor->GetLocalBounds(MinBounds, MaxBounds);

	MinBounds += CursorWorldPosition;
	MaxBounds += CursorWorldPosition;

	const auto Bounds = {MinBounds, FVector{MinBounds.X, MaxBounds.Y, MinBounds.Z}, FVector{MaxBounds.X, MinBounds.Y,	MaxBounds.Z}, MaxBounds};
	
	float Height = 0;

	for (auto Bound : Bounds)
	{
		float testHeight = GetClosestToScreenAtPosition(Bound);
		if (testHeight > Height)
		{
			Height = testHeight;
		}
	}
	
	return Height + HeightAboveSurface;
}

float ACameraCursor::GetClosestToScreenAtPosition(const FVector& TracePosition)
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

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);
	
	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByObjectType(
		RV_Hit,
		WorldLocation,
		WorldLocation + (WorldDirection * 10000.0f), 
		ECC_WorldStatic,
		RV_TraceParams
	);

	if (RV_Hit.bBlockingHit)
	{
		return RV_Hit.ImpactPoint.Z;
	}
	
	return -1;
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

ACameraCursor::ECursorSpace ACameraCursor::GetCursorSpace()
{
	return CursorSpace;
}
