// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/LivesHandler.h"
#include "Interfaces/LivesStateUpdater.h"
#include "BaseRTSGameState.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAMEMODE_API ABaseRTSGameState : public AGameStateBase, public ILivesStateUpdater, public ILivesHandler
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FLivesChanged OnLivesChanged;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, ReplicatedUsing = OnRep_LivesChanged)
	int Lives = 20;

	UFUNCTION(BlueprintCallable)
	virtual void LoseLife() override;

	virtual void EndGame();

	UFUNCTION()
	void OnRep_LivesChanged();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void RegisterLivesChanged_Implementation(const FLivesChangedParameter& CallbackFunc) override;
	virtual void UnregisterLivesChanged_Implementation(const FLivesChangedParameter& CallbackFunc) override;
	virtual void InitializeLivesState_Implementation(const FLivesChangedParameter& CallbackFunc) override;
};
