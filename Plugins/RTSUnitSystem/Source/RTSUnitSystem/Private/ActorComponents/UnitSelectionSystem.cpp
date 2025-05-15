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

void UUnitSelectionSystem::SelectUnit(AActor* SelectedUnit, const ESelectStyle SelectionStyle, const int Sender)
{
	switch (SelectionStyle)
	{
	case ESelectStyle::New:
		{
			ClearSelectedUnits();
			SelectUnitInternal(SelectedUnit);
			break;
		}
	case ESelectStyle::Add:
		{
			bool Clear = false;
			if (SelectedUnits.Num() > 0)
			{
				// Can only multi-select units that are on your team
				if (SelectedUnits[0].GetSide().Team != Sender)
				{
					Clear = true;
				}
			}
			FSelected NewUnit;
			NewUnit.TrySelect(SelectedUnit);
			if (NewUnit.GetSide().Team == Sender)
			{
				// If we're currently selecting an enemy unit and Add Click on an allied unit, start a new selection
				if (Clear)
				{
					ClearSelectedUnits();
				}
				SelectUnitInternal(SelectedUnit);
			}
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

void UUnitSelectionSystem::ClearSelectedUnits()
{
	for (auto Unit : SelectedUnits)
	{
		Unit.Select(nullptr);
	}
	SelectedUnits.Empty();
}

void UUnitSelectionSystem::SelectUnitInternal(AActor* SelectedUnit)
{
	FSelected NewUnit;
	NewUnit.Select(SelectedUnit);
	if (NewUnit.Selected())
	{
		if (SelectedUnits.Num() == 1)
		{
			SelectedUnits[0].HideUI();
		}
		SelectedUnits.Add(NewUnit);
		if (SelectedUnits.Num() == 1)
		{
			NewUnit.ShowUI();
		}
	}
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

