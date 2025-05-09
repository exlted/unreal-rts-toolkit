// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerPawn.h"

#include "AssetTypeCategories.h"
#include "Utils/Trace.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ARTSPlayerPawn::ARTSPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 2500.0f;
	SpringArm->SetRelativeRotation(FRotator(-85.0f, 0.0, 0.0f));
	SpringArm->bEnableCameraRotationLag = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	WorldCursor = CreateDefaultSubobject<UStaticMeshComponent>("WorldCursor");
	WorldCursor->SetupAttachment(RootComponent);
	WorldCursor->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	WorldCursor->SetCollisionResponseToChannels(ECR_Ignore);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
}

// Called when the game starts or when spawned
void ARTSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	ZoomCameraAbsolute(ZoomLevel);
	TargetCursorMode = CursorMode;
	CursorMode = ECursorMode::Unset;
	TargetVisibilityState = Visible;
}

// Called every frame
void ARTSPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetLocalViewingPlayerController() != nullptr)
	{
		if (CursorMode != TargetCursorMode)
		{
			ChangeCursorMode(TargetCursorMode);
		}

		if (Visible != TargetVisibilityState)
		{
			ChangeCursorVisibility(TargetVisibilityState);
		}
	}
}

// Called to bind functionality to input
void ARTSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARTSPlayerPawn::ChangeCursorVisibility(const bool NewVisibilityState)
{
	TargetVisibilityState = NewVisibilityState;
	if (GetLocalViewingPlayerController() != nullptr)
	{
		if (TargetVisibilityState == true)
		{
			switch (CursorMode)
			{
			case ECursorMode::World:
				WorldCursor->SetVisibility(true, true);
				break;
			case ECursorMode::Screen:
				GetLocalViewingPlayerController()->bShowMouseCursor = true;
				break;
			case ECursorMode::Unset:
				break;
			}
			Visible = true;
		}
		else
		{
			WorldCursor->SetVisibility(false, true);
			GetLocalViewingPlayerController()->bShowMouseCursor = false;
			Visible = false;
		}
	}
}

bool ARTSPlayerPawn::GetCursorVisibility() const
{
	return Visible;
}

void ARTSPlayerPawn::ChangeCursorMode(const ECursorMode NewCursorMode)
{
	TargetCursorMode = NewCursorMode;

	if (GetLocalViewingPlayerController() != nullptr)
	{
		switch (TargetCursorMode)
		{
		case ECursorMode::World:
			WorldCursor->SetVisibility(Visible, true);
			GetLocalViewingPlayerController()->bShowMouseCursor = false;
			CursorMode = ECursorMode::World;
			break;
		case ECursorMode::Screen:
			WorldCursor->SetVisibility(false, true);
			GetLocalViewingPlayerController()->bShowMouseCursor = Visible;
			CursorMode = ECursorMode::Screen;
			break;
		case ECursorMode::Unset:
			break;
		}
	}
}

ECursorMode ARTSPlayerPawn::GetCursorMode() const
{
	return CursorMode;
}

void ARTSPlayerPawn::MoveCursorToCameraRelativePosition(const FVector& MousePosition, const FVector& MouseDirection) const
{
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	const FHitResult RV_Hit = DoSingleLineTrace(
		this,
		UE::Geometry::TSegment3<double>(MousePosition, MouseDirection, 10000.0f),
		ECC_WorldStatic,
		RV_TraceParams);

	if (RV_Hit.bBlockingHit)
	{
		MoveCursorTo(RV_Hit.ImpactPoint);
	}
	else
	{
		const auto RootPosition = this->GetActorLocation();
		
		// If there isn't an intersection on the Trace, Place it on the RootPosition
		const FVector EndLocation = FMath::LinePlaneIntersection(
					   MousePosition,
					   MousePosition + (MouseDirection * 10000.0f),
					   RootPosition,
					   FVector{0.f, 0.f, 1.f});

		MoveCursorTo(EndLocation);
	}
}

void ARTSPlayerPawn::MoveCursorTo(const FVector& WorldSpaceCoordinates) const
{
	const auto RootPosition = this->GetActorLocation();
	const FVector FilteredPosition = FVector(WorldSpaceCoordinates.X - RootPosition.X, WorldSpaceCoordinates.Y - RootPosition.Y,
		GetClosestToScreenAtPosition(WorldSpaceCoordinates) + HeightAboveSurface - RootPosition.Z);
			
	WorldCursor->SetRelativeLocation(FilteredPosition);
}

void ARTSPlayerPawn::MoveCursorTo(const FVector2D& ScreenSpaceCoordinates) const
{
	const auto PlayerController = GetLocalViewingPlayerController();
	FVector WorldLocation;
	FVector WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(ScreenSpaceCoordinates.X, ScreenSpaceCoordinates.Y,
		WorldLocation, WorldDirection);

	MoveCursorToCameraRelativePosition(WorldLocation, WorldDirection);
}

void ARTSPlayerPawn::ResetCursorPosition() const
{
	WorldCursor->SetRelativeLocation(FVector(0, 0, WorldCursor->GetRelativeLocation().Z));
}

FVector ARTSPlayerPawn::GetCursorLocation() const
{
	return WorldCursor->GetRelativeLocation() + GetActorLocation();
}

FVector2D ARTSPlayerPawn::GetCursorScreenLocation() const
{
	const auto PlayerController = GetLocalViewingPlayerController();

	FVector2D ScreenPosition;
	PlayerController->GetMousePosition(ScreenPosition.X, ScreenPosition.Y);
	
	return ScreenPosition;
}

void ARTSPlayerPawn::ZoomCamera(const float Amount)
{
	ZoomCameraAbsolute(ZoomLevel + Amount);
}

void ARTSPlayerPawn::ZoomCameraAbsolute(float NewZoom)
{
	if (NewZoom > 1)
	{
		NewZoom = 1;
	}
	else if (NewZoom < 0)
	{
		NewZoom = 0;
	}

	ZoomLevel = NewZoom;

	SpringArm->TargetArmLength = ZoomCurve->GetFloatValue(ZoomLevel);
	FRotator NewRotation = SpringArm->GetRelativeRotation();
	NewRotation.Pitch = PitchCurve->GetFloatValue(ZoomLevel);
	SpringArm->SetRelativeRotation(NewRotation);
	
	if (fabs(NewRotation.Pitch) < SwapPitch && CursorMode == ECursorMode::World)
	{
		ChangeCursorMode(ECursorMode::Screen);
	}
	else if (fabs(NewRotation.Pitch) > SwapPitch && CursorMode == ECursorMode::Screen)
	{
		ChangeCursorMode(ECursorMode::World);
	}
}

float ARTSPlayerPawn::GetZoom()
{
	return ZoomLevel;
}

void ARTSPlayerPawn::RotateCamera(const float Amount)
{
	RotateCameraAbsolute(SpringArm->GetRelativeRotation().Yaw + Amount);
}

void ARTSPlayerPawn::RotateCameraAbsolute(const float NewRotation)
{
	auto Rotation = SpringArm->GetRelativeRotation();
	Rotation.Yaw = NewRotation;

	if (Rotation.Yaw > 360.0f)
	{
		Rotation.Yaw -= 360.0f;
	}
	else if (Rotation.Yaw < 0)
	{
		Rotation.Yaw += 360.0f;
	}

	SpringArm->SetRelativeRotation(Rotation);
}

float ARTSPlayerPawn::GetRotation()
{
	return SpringArm->GetRelativeRotation().Yaw;
}

float ARTSPlayerPawn::GetClosestToScreenAtPosition(const FVector& TracePosition) const
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
		UE::Geometry::TSegment3<double>(WorldLocation, WorldDirection, 10000.0f),
		ECC_WorldStatic,
		RV_TraceParams);

	if (RV_Hit.bBlockingHit)
	{
		return RV_Hit.ImpactPoint.Z;
	}

	// If we didn't hit anything, we're probably in the void, so treat as if we hit at 0
	return 0;
}

