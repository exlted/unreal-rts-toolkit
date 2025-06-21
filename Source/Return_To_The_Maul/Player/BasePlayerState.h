// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/UnitSelectionSystem.h"
#include "ActorComponents/UnitSpawningSystem.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/HasSide.h"
#include "Interfaces/HasUIManager.h"
#include "Interfaces/WaveVoteHandler.h"
#include "Structs/FSide.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API ABasePlayerState : public APlayerState, public IHasSide
	, public IHasUIManager, public IWaveVoteHandler
{
	GENERATED_BODY()

	ABasePlayerState();
	
public:
	UPROPERTY(Replicated, EditAnywhere)
	FSide Side;

	UPROPERTY(EditAnywhere)
	UUnitSelectionSystem* UnitSelectionSystem;

	UPROPERTY(EditAnywhere)
	UUnitSpawningSystem* UnitSpawningSystem;

	UPROPERTY(EditAnywhere)
	UUIManager* UIManager;
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetPlayerNum(int TeamNumber);
	void SetColor(FColor Color);

	void SpawnEntities(const FTransform& SpawnLocation);

	virtual FSide GetSide() override;

	virtual TWeakObjectPtr<UUIManager> GetUIManager() override;

	UFUNCTION(Server, Reliable)
	void StartNextWave();
	
	virtual void VoteStartNextWave_Implementation() override;
	virtual void RevokeVoteStartNextWave_Implementation() override;

	UFUNCTION(Server, Reliable)
	void VoteNextWave(bool Revoke);
};
