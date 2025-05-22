// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/TeamColorizer.h"

#include "Structs/FSide.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UTeamColorizer::UTeamColorizer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeamColorizer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (MeshComponent == nullptr)
	{
		MeshComponent = GetRelatedSingletonTypedComponents<UMeshComponent>(GetOwner());
	}
	TargetableComponent = GetRelatedSingletonComponent<ITargetable, UTargetable>(GetOwner());
	if (MeshComponent != nullptr && TargetableComponent != nullptr)
	{
		TargetableComponent->RegisterSideUpdates(this, &UTeamColorizer::OnSideChanged);
	}
}


// Called every frame
void UTeamColorizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTeamColorizer::OnSideChanged(const FSide SideUpdate)
{
	if (MeshComponent != nullptr && Enabled)
	{
		const auto TeamMaterial = UMaterialInstanceDynamic::Create(BaseTeamMaterial, this);
		TeamMaterial->SetVectorParameterValue("TeamColor", SideUpdate.UnitColor);

		// How do we configurably get a Mesh to set a Material to?
		MeshComponent->SetMaterial(0, TeamMaterial);
	}
}

void UTeamColorizer::Disable()
{
	Enabled = false;
}

