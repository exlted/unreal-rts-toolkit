// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"

#include <string>

#include "Net/UnrealNetwork.h"

ABasePlayerState::ABasePlayerState()
{
	UnitSelectionSystem = CreateDefaultSubobject<UUnitSelectionSystem>("UnitSelectionSystem");
	UnitSpawningSystem = CreateDefaultSubobject<UUnitSpawningSystem>("UnitSpawningSystem");
	UIManager = CreateDefaultSubobject<UUIManager>("UUIManager");
}

void ABasePlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	UnitSpawningSystem->SetSide(Side);
}

void ABasePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasePlayerState, Side);
}

void ABasePlayerState::SetTeam(const int TeamNumber)
{
	Side.Team = TeamNumber;

	UnitSpawningSystem->SetSide(Side);
}

void ABasePlayerState::SetColor(const FColor Color)
{
	Side.UnitColor = Color;

	UnitSpawningSystem->SetSide(Side);
}

void ABasePlayerState::MoveSelectedUnit(const FVector& GoalPosition, int Sender)
{
	if (UnitSelectionSystem != nullptr)
	{
		if (Sender == -1)
		{
			Sender = Side.Team;
		}
		
		UnitSelectionSystem->MoveSelectedUnit(GoalPosition, Sender);
	}
}

void ABasePlayerState::SelectUnit(AActor* SelectedUnit, const ESelectStyle SelectionStyle, int Sender)
{
	if (UnitSelectionSystem != nullptr)
	{
		if (Sender == -1)
		{
			Sender = Side.Team;
		}
		
		UnitSelectionSystem->SelectUnit(SelectedUnit, SelectionStyle, Sender);
	}
}

void ABasePlayerState::SpawnEntities(const FTransform& SpawnLocation)
{
	for (const auto [Entity, SpawnOffset] : Side.Faction.InitialEntities)
	{
		UnitSpawningSystem->SpawnEntity(this, Entity, SpawnLocation + SpawnOffset);
	}
}

FSide ABasePlayerState::GetSide()
{
	return Side;
}

TWeakObjectPtr<UUIManager> ABasePlayerState::GetUIManager()
{
	return UIManager;
}
