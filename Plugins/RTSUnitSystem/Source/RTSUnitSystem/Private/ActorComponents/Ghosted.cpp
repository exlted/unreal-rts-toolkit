// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Ghosted.h"

#include "Components/CapsuleComponent.h"
#include "Interfaces/Attachable.h"
#include "Interfaces/ModularPlayerController.h"
#include "Utils/ActorUtils.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UGhosted::UGhosted()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGhosted::BeginPlay()
{
	Super::BeginPlay();

	int ActionCount = 0;
	
	// Find Mesh components on the parent, replace their materials with our Ghost material
	if (GhostedMaterial != nullptr)
	{
		for (const auto Meshes = GetRelatedTypedComponents<UMeshComponent>(GetOwner());
			 const auto& Mesh : Meshes)
		{
			const auto Materials = Mesh->GetMaterials();
			for (int i = 0; i < Materials.Num(); ++i)
			{
				Mesh->SetMaterial(i, GhostedMaterial);
			}
		}
		ActionCount++;
	}

	// Attach this Actor to the Camera's "Cursor" Attachment Point
	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (const auto Pawn = Controller->GetPawnOrSpectator(); Pawn != nullptr)
	{
		if (const auto Attachable = GetRelatedSingletonComponent<IAttachable, UAttachable>(Pawn);
			Attachable != nullptr)
		{
			Attachable->AttachTo(GetOwner(), "Cursor");
			GetOwner()->SetActorScale3D(FVector(1.f, 1.f, 1.f));
			// Snap to floor
			if (const auto Capsule = GetRelatedSingletonTypedComponents<UCapsuleComponent>(GetOwner());
				Capsule != nullptr)
			{
				// For Characters, by default Capsules are half below the floor and half above, so, move the character
				//   up by half the capsule's height
				GetOwner()->SetActorRelativeLocation(FVector(0, 0, Capsule->GetUnscaledCapsuleHalfHeight()));
			}
		}
		ActionCount++;
	}
	
	// Switch Control Mode to Building mode
	if (const auto ModularController = GetSingletonInterface<IModularPlayerController, UModularPlayerController>(Controller);
		ModularController != nullptr)
	{
		ModularController->PushNamedComponent("Building");
		ActionCount++;
	}
	// Turn off collision
	GetOwner()->SetActorEnableCollision(false);

	if (ActionCount < 3)
	{
		// Log that we failed to create the ghosted item & destroy it
		GetOwner()->Destroy();
	}
}

void UGhosted::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Detach this Actor from the Camera's Cursor
	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (const auto Pawn = Controller->GetPawnOrSpectator(); Pawn != nullptr)
	{
		if (const auto Attachable = GetRelatedSingletonComponent<IAttachable, UAttachable>(Pawn);
			Attachable != nullptr)
		{
			Attachable->DetachFrom("Cursor");
		}
	}
	// Pop the Control Mode
	if (Controller->Implements<UModularPlayerController>())
	{
		if (const auto ModularController = TScriptInterface<IModularPlayerController>(Controller);
			ModularController != nullptr)
		{
			ModularController->PopComponent();
		}
	}
}


// Called every frame
void UGhosted::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

