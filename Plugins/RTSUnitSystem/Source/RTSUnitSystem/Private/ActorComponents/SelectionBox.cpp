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
		this->DecalMaterial = OwnedUnit;
		break;
	case EUnitRelationType::Friendly:
		this->DecalMaterial = FriendlyUnit;
		break;
	case EUnitRelationType::Neutral:
		this->DecalMaterial = NeutralUnit;
		break;
	case EUnitRelationType::Enemy:
		this->DecalMaterial = EnemyUnit;
		break;
	}
}

