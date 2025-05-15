#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Builder.h"
#include "Interfaces/Movable.h"
#include "Interfaces/Selectable.h"
#include "Interfaces/Targetable.h"
#include "Utils/ComponentUtils.h"
#include "FSelected.generated.h"

USTRUCT(BlueprintType)
struct FSelected
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TScriptInterface<ISelectable> SelectedUnit;
	
	UPROPERTY(EditAnywhere)
	TScriptInterface<IMovable> MovableUnit;

	UPROPERTY(EditAnywhere)
	TScriptInterface<ITargetable> TargetableUnit;

	UPROPERTY(EditAnywhere)
	TScriptInterface<IBuilder> BuilderUnit;

	void TrySelect(AActor* PotentialSelection)
	{
		if (PotentialSelection != nullptr)
		{
			SelectedUnit = GetRelatedSingletonComponent<ISelectable, USelectable>(PotentialSelection);
			MovableUnit = GetRelatedSingletonComponent<IMovable, UMovable>(PotentialSelection);
			TargetableUnit = GetRelatedSingletonComponent<ITargetable, UTargetable>(PotentialSelection);
			BuilderUnit = GetRelatedSingletonComponent<IBuilder, UBuilder>(PotentialSelection);
		}
	}
	
	void Select(AActor* SelectedActor)
	{
		if (SelectedUnit == nullptr && SelectedActor == nullptr)
		{
			return;
		}
		
		if (SelectedUnit != nullptr)
		{
			if (SelectedActor == Cast<UActorComponent>(SelectedUnit.GetObject())->GetOwner())
			{
				// no change, no work needed
				return;
			}
			
			// If we already have something selected, and we're deselecting it, let it know
			SelectedUnit->OnDeselect();
			BuilderUnit->HideUI();
			SelectedUnit = nullptr;
			MovableUnit = nullptr;
			BuilderUnit = nullptr;
		}

		if (SelectedActor != nullptr)
		{
			SelectedUnit = GetRelatedSingletonComponent<ISelectable, USelectable>(SelectedActor);
			if (SelectedUnit != nullptr)
			{
				SelectedUnit->OnSelect();
			}
			MovableUnit = GetRelatedSingletonComponent<IMovable, UMovable>(SelectedActor);
			TargetableUnit = GetRelatedSingletonComponent<ITargetable, UTargetable>(SelectedActor);
			BuilderUnit = GetRelatedSingletonComponent<IBuilder, UBuilder>(SelectedActor);
		}
	}

	bool Selected() const
	{
		return SelectedUnit != nullptr;
	}
	
	bool CanMove() const
	{
		return MovableUnit != nullptr;
	}
	
	void MoveTo(const FVector& NewLocation) const 
	{
		if (MovableUnit != nullptr)
		{
			MovableUnit->MoveTo(NewLocation);
		}
	}

	FSide GetSide() const
	{
		if (TargetableUnit != nullptr)
		{
			return TargetableUnit->GetSide();
		}
		FSide EmptySide;
		EmptySide.PlayerTag = FName("None");
		EmptySide.Team = -1;
		EmptySide.UnitColor = FColor::Transparent;
		EmptySide.Faction.InitialEntities = TArray<FSpawnInfo>();
		
		return EmptySide;
	}

	void ShowUI() const
	{
		if (BuilderUnit != nullptr)
		{
			BuilderUnit->DisplayUI();
		}
	}

	void HideUI() const
	{
		if (BuilderUnit != nullptr)
		{
			BuilderUnit->HideUI();
		}
	}
};
