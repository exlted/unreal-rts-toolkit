// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRTSGameState.h"

#include "Net/UnrealNetwork.h"

void ABaseRTSGameState::LoseLife()
{
	Lives -= 1;

	if (Lives <= 0)
	{
		EndGame();
	}
}

void ABaseRTSGameState::EndGame()
{
	//TODO: Transition to End Game Scene, passing all data stored during this game to it
}

void ABaseRTSGameState::OnRep_LivesChanged()
{
	OnLivesChanged.Broadcast(Lives);
}

void ABaseRTSGameState::OnRep_VotesChanged()
{
	if (Votes > RequiredVoteCount)
	{
		StartNextWave();
	}
}

void ABaseRTSGameState::OnRep_SpawnersChanged()
{
	OnNextWave.Broadcast(CollectNextWave());
}

void ABaseRTSGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseRTSGameState, Lives);
	DOREPLIFETIME(ABaseRTSGameState, Votes);
	DOREPLIFETIME(ABaseRTSGameState, RequiredVoteCount);
	DOREPLIFETIME(ABaseRTSGameState, Spawners);
}

void ABaseRTSGameState::RegisterLivesChanged_Implementation(const FLivesChangedParameter& CallbackFunc)
{
	OnLivesChanged.Add(CallbackFunc);
}

void ABaseRTSGameState::UnregisterLivesChanged_Implementation(const FLivesChangedParameter& CallbackFunc)
{
	OnLivesChanged.Remove(CallbackFunc);
}

void ABaseRTSGameState::InitializeLivesState_Implementation(const FLivesChangedParameter& CallbackFunc)
{
	CallbackFunc.ExecuteIfBound(Lives);
}

void ABaseRTSGameState::VoteStartNextWave_Implementation()
{
	Votes += 1;
}

void ABaseRTSGameState::RevokeVoteStartNextWave_Implementation()
{
	Votes -= 1;
}

void ABaseRTSGameState::RegisterWaveDataCallback_Implementation(const FNextWaveParameter& Callback)
{
	OnNextWave.Add(Callback);
}

void ABaseRTSGameState::UnregisterWaveDataCallback_Implementation(const FNextWaveParameter& Callback)
{
	OnNextWave.Remove(Callback);
}

void ABaseRTSGameState::InitializeNextWaveData_Implementation(const FNextWaveParameter& Callback)
{
	Callback.ExecuteIfBound(CollectNextWave());
}

TArray<FDataTableRowHandle> ABaseRTSGameState::CollectNextWave()
{
	TArray<FDataTableRowHandle> NextWaveContents;
	for (const auto Spawner : Spawners)
	{
		if (Spawner->HasAnotherWave())
		{
			for (const auto Wave = Spawner->GetNextWave();
				const auto [EntityInfo, SpawnOffset] : Wave.CreepsToSpawn)
			{
				NextWaveContents.Add(EntityInfo);
			}
		}
	}

	return NextWaveContents;
}

void ABaseRTSGameState::StartNextWave()
{
	int WavesSent = 0;
	for (const auto& Spawner : Spawners)
	{
		if (Spawner->HasAnotherWave())
		{
			Spawner->SpawnNextWave();
			WavesSent += 1;
		}
	}

	if (WavesSent == 0)
	{
		EndGame();
		return;
	}
	
	OnNextWave.Broadcast(CollectNextWave());
	Votes = 0;
}

void ABaseRTSGameState::RegisterSpawner(const TScriptInterface<IAutoSpawner> NewSpawner)
{
	Spawners.Add(NewSpawner);
}
