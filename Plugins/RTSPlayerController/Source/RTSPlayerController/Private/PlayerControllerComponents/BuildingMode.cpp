// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerComponents/BuildingMode.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerState.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UBuildingMode::UBuildingMode()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildingMode::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UBuildingMode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (!Spawner && Controller != nullptr && Controller->PlayerState != nullptr)
	{
		Spawner = GetRelatedSingletonComponent<ISpawner, USpawner>(Controller->PlayerState);
	}
}

void UBuildingMode::Enable()
{
	Enabled = true;
	EnhancedInputSubsystem->AddMappingContext(BuilderMappingContext, 1);
}

void UBuildingMode::Disable()
{
	Enabled = false;
	EnhancedInputSubsystem->RemoveMappingContext(BuilderMappingContext);
}

void UBuildingMode::SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
	UEnhancedInputComponent* EnhancedInputComponent, APlayerController* PlayerController)
{
	EnhancedInputSubsystem = Subsystem;

	
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &UBuildingMode::OnRotateTriggered);
		EnhancedInputComponent->BindAction(AddModifierAction, ETriggerEvent::Triggered, this, &UBuildingMode::OnAddModifierTriggered);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &UBuildingMode::OnClickTriggered);
		EnhancedInputComponent->BindAction(CancelClickAction, ETriggerEvent::Triggered, this, &UBuildingMode::OnCancelClickTriggered);
	}

	Controller = PlayerController;
}

bool UBuildingMode::IsBaseController()
{
	return false;
}

FName UBuildingMode::GetIdentifier()
{
	return "Building";
}

void UBuildingMode::OnRotateTriggered(const FInputActionInstance& Instance)
{
	if (Enabled && Spawner != nullptr)
	{
		if (const auto Actor = Spawner->GetPlayerDefinedEntity().Pin();
			Actor != nullptr)
		{
			// Rotate the actor
			auto Rotation = Actor->GetActorRotation();
			Rotation.Yaw += Instance.GetValue().Get<float>();

			if (Rotation.Yaw > 360.0f)
			{
				Rotation.Yaw -= 360.0f;
			}
			else if (Rotation.Yaw < 0)
			{
				Rotation.Yaw += 360.0f;
			}

			Actor->SetActorRotation(Rotation);
		}
	}
}

void UBuildingMode::OnAddModifierTriggered(const FInputActionInstance& Instance)
{
	if (Enabled)
	{
		const auto Test = Instance.GetValue();
		const auto Test2 = Test.Get<bool>();
		AddModifierPressed = Test2;
	}
}

void UBuildingMode::OnClickTriggered()
{
	if (Enabled && Spawner != nullptr)
	{
		Spawner->FinishPlayerDefinedEntity(this, AddModifierPressed);
	}
}

void UBuildingMode::OnCancelClickTriggered()
{
	if (Enabled && Spawner != nullptr)
	{
		Spawner->CancelPlayerDefinedEntity();
	}
}

