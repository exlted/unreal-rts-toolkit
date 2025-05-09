// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/UnitSelectionSystem.h"


// Sets default values for this component's properties
UUnitSelectionSystem::UUnitSelectionSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnitSelectionSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUnitSelectionSystem::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUnitSelectionSystem::MoveSelectedUnit(const FVector& GoalPosition, const int Sender)
{
	MoveUnits(GetSelectedUnits(), GoalPosition, Sender);
}

void UUnitSelectionSystem::SelectUnit(AActor* SelectedUnit, const ESelectStyle SelectionStyle)
{
	switch (SelectionStyle)
	{
	case ESelectStyle::New:
		{
			for (auto Unit : SelectedUnits)
			{
				Unit.Select(nullptr);
			}
			SelectedUnits.Empty();

			FSelected NewUnit;
			NewUnit.Select(SelectedUnit);
			SelectedUnits.Add(NewUnit);
			break;
		}
	case ESelectStyle::Add:
		{
			FSelected NewUnit;
			NewUnit.Select(SelectedUnit);
			SelectedUnits.Add(NewUnit);
			break;
		}
	case ESelectStyle::Group:
		// Add Support for Select Groups here
		break;
	}
}

TArray<FSelected> UUnitSelectionSystem::GetSelectedUnits()
{
	return SelectedUnits;
}

void UUnitSelectionSystem::MoveUnits_Implementation(const TArray<FSelected>& Units, const FVector& GoalPosition, const int Sender)
{
	// TODO: Implement Formation Support Here?
	for (const auto& Unit : Units)
	{
		if (Unit.GetSide().Team == Sender)
		{
			Unit.MoveTo(GoalPosition);
		}
	}
}

