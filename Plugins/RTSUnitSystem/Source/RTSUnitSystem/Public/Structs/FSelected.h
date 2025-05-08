#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Movable.h"
#include "Interfaces/Selectable.h"
#include "Interfaces/Targetable.h"
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
	
	void Select(AActor* SelectedActor)
	{
		if (SelectedActor == SelectedUnit.GetObject())
		{
			// no change, no work needed
			return;
		}
		
		// If we already have something selected, and we're deselecting it, let it know
		if (SelectedUnit != nullptr)
		{
			SelectedUnit->OnDeselect();
			SelectedUnit = nullptr;
			MovableUnit = nullptr;
		}

		if (SelectedActor != nullptr && SelectedActor->Implements<USelectable>())
		{
			SelectedUnit = TScriptInterface<ISelectable>(SelectedActor);
			SelectedUnit->OnSelect();
			if (SelectedActor->Implements<UMovable>())
			{
				MovableUnit = TScriptInterface<IMovable>(SelectedActor);
			}
			if (SelectedActor->Implements<UTargetable>())
			{
				TargetableUnit = TScriptInterface<ITargetable>(SelectedActor);
			}
		}
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
};
