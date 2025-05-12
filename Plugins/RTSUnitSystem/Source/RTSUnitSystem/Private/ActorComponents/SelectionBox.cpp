// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/SelectionBox.h"


// Sets default values for this component's properties
USelectionBox::USelectionBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetRelativeRotation(FRotator(0, 0, 90));
	DecalSize = FVector(10, 20, 20);
	SetRelativeLocation(FVector(0, 0, -30));
}


// Called when the game starts
void USelectionBox::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USelectionBox::SetDecalMaterial(UMaterialInstance* Material)
{
	if (Material != nullptr)
	{
		DecalMaterial = Material;
	}
}


// Called every frame
void USelectionBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USelectionBox::SetUnitRelation(const EUnitRelationType Relation)
{
	switch (Relation)
	{
	case EUnitRelationType::Owned:
		SetDecalMaterial(OwnedUnit);
		break;
	case EUnitRelationType::Friendly:
		SetDecalMaterial(FriendlyUnit);
		break;
	case EUnitRelationType::Neutral:
		SetDecalMaterial(NeutralUnit);
		break;
	case EUnitRelationType::Enemy:
		SetDecalMaterial(EnemyUnit);
		break;
	case EUnitRelationType::Unset:
		break;
	}
}

void USelectionBox::OnSelect()
{
	SetVisibility(true);
}

void USelectionBox::OnDeselect()
{
	SetVisibility(false);
}

bool USelectionBox::HasTag(const FName TagName)
{
	return GetOwner()->Tags.Contains(TagName);
}

