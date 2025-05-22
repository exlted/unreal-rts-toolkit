// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Utils/ComponentUtils.h"

ABasePlayerController::ABasePlayerController()
{
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	Components = GetRelatedComponents<IPlayerControllerComponent, UPlayerControllerComponent>(this);
	const auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());	
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	for (auto Component : Components)
	{
		Component->SetupInputComponent(InputSubsystem, EnhancedInputComponent, this);

		if (!Component->IsBaseController())
		{
			NamedComponents.Add(Component->GetIdentifier(), Component);
		}
		else
		{
			BaseComponents.Add(Component);
			Component->Enable();
		}
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

TArray<FName> ABasePlayerController::GetNamedComponents()
{
	TArray<FName> ComponentNames;

	for (auto ComponentInfo : NamedComponents)
	{
		ComponentNames.Add(ComponentInfo.Key);
	}
	
	return ComponentNames;
}

void ABasePlayerController::PushNamedComponent(const FName Name)
{
	if (NamedComponents.Contains(Name))
	{
		if (const auto Component = NamedComponents.Find(Name); Component != nullptr)
		{
			if (ComponentStack.Num() == 0)
			{
				for (const auto BaseComponent : BaseComponents)
				{
					BaseComponent->Disable();
				}
			}
			
			Component->GetInterface()->Enable();
			ComponentStack.Push(*Component);
		}
	}
}

bool ABasePlayerController::PopComponent()
{
	if (ComponentStack.Num() > 0)
	{
		if (const auto OldTop = ComponentStack.Pop())
		{
			OldTop->Disable();
		}

		if (ComponentStack.Num() == 0)
		{
			for (const auto Component : BaseComponents)
			{
				Component->Enable();
			}
		}
	}
	
	return ComponentStack.Num() != 0;
}
