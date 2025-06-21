// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/AutoSpawner.h"
#include "Interfaces/GameController.h"
#include "Interfaces/LivesHandler.h"
#include "Interfaces/LivesStateUpdater.h"
#include "Interfaces/WaveHandler.h"
#include "BaseRTSGameState.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAMEMODE_API ABaseRTSGameState : public AGameStateBase, public ILivesStateUpdater, public ILivesHandler
	, public IWaveHandler, public IGameController, public IWaveVoteHandler
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FLivesChanged OnLivesChanged;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, ReplicatedUsing = OnRep_LivesChanged)
	int Lives = 20;

	UPROPERTY(EditAnywhere, Replicated, ReplicatedUsing = OnRep_VotesChanged)
	int Votes = 0;

	UPROPERTY(EditAnywhere, Replicated)
	int RequiredVoteCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FNextWave OnNextWave;
	
	UPROPERTY(EditAnywhere, Replicated, ReplicatedUsing = OnRep_SpawnersChanged)
	TArray<TScriptInterface<IAutoSpawner>> Spawners;
	
	UFUNCTION(BlueprintCallable)
	virtual void LoseLife() override;

	virtual void EndGame();

	UFUNCTION()
	void OnRep_LivesChanged();

	UFUNCTION()
	void OnRep_VotesChanged();

	UFUNCTION()
	void OnRep_SpawnersChanged();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void RegisterLivesChanged_Implementation(const FLivesChangedParameter& CallbackFunc) override;
	virtual void UnregisterLivesChanged_Implementation(const FLivesChangedParameter& CallbackFunc) override;
	virtual void InitializeLivesState_Implementation(const FLivesChangedParameter& CallbackFunc) override;

	virtual void VoteStartNextWave_Implementation() override;
	virtual void RevokeVoteStartNextWave_Implementation() override;
	virtual void RegisterWaveDataCallback_Implementation(const FNextWaveParameter& Callback) override;
	virtual void UnregisterWaveDataCallback_Implementation(const FNextWaveParameter& Callback) override;
	virtual void InitializeNextWaveData_Implementation(const FNextWaveParameter& Callback) override;

	TArray<FDataTableRowHandle> CollectNextWave();
	
	virtual void StartNextWave() override;
	virtual void RegisterSpawner(TScriptInterface<IAutoSpawner> NewSpawner) override;
};
