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

void ABaseRTSGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseRTSGameState, Lives);
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
