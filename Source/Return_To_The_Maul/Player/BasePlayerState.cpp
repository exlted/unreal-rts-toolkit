// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Return_To_The_Maul/GameMode/RTSGameModeBase.h"

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

	if (!UIManager)
	{
		UIManager = GetRelatedSingletonTypedComponents<UUIManager>(this);
	}
}

void ABasePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasePlayerState, Side);
}

void ABasePlayerState::SetPlayerNum(const int TeamNumber)
{
	Side.Team = TeamNumber;

	UnitSpawningSystem->SetSide(Side);
}

void ABasePlayerState::SetColor(const FColor Color)
{
	Side.UnitColor = Color;

	UnitSpawningSystem->SetSide(Side);
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

void ABasePlayerState::StartNextWave_Implementation()
{
	if (const auto GameController = GetRelatedSingletonComponent<IGameController, UGameController>(GetWorld()->GetAuthGameMode());
		GameController != nullptr)
	{
		GameController->StartNextWave();
	}
}
