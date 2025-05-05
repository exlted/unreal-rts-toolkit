#pragma once

#include "CoreMinimal.h"
#include "Return_To_The_Maul/Interfaces/Movable.h"
#include "Return_To_The_Maul/Interfaces/Selectable.h"
#include "FSelected.generated.h"

USTRUCT(BlueprintType)
struct FSelected
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	TScriptInterface<ISelectable> SelectedUnit;
	
	UPROPERTY(EditAnywhere)
	TScriptInterface<IMovable> MovableUnit;

public:
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
};
