// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"

ABasePlayerState::ABasePlayerState()
{
	UnitSelectionSystem = CreateDefaultSubobject<UUnitSelectionSystem>("UnitSelectionSystem");
	UnitSpawningSystem = CreateDefaultSubobject<UUnitSpawningSystem>("UnitSpawningSystem");
}

void ABasePlayerState::BeginPlay()
{
	Super::BeginPlay();

	//if (const auto Pawn = GetPlayerController()->GetPawnOrSpectator(); Pawn != nullptr)
	//{
	//	Side.Faction.SpawnInitialEntities(GetWorld(), Pawn->GetTransform(), this);
	//}
}

void ABasePlayerState::MoveSelectedUnit(const FVector& GoalPosition)
{
	if (UnitSelectionSystem != nullptr)
	{
		UnitSelectionSystem->MoveSelectedUnit(GoalPosition);
	}
}

void ABasePlayerState::SelectUnit(AActor* SelectedUnit, const ESelectStyle SelectionStyle)
{
	if (UnitSelectionSystem != nullptr)
	{
		UnitSelectionSystem->SelectUnit(SelectedUnit, SelectionStyle);
	}
}
