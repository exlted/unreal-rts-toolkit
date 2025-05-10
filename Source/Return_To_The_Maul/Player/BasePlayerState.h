// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/UnitSelectionSystem.h"
#include "ActorComponents/UnitSpawningSystem.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/HasSide.h"
#include "Structs/FSide.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API ABasePlayerState : public APlayerState, public IMoveUnit, public ISelectUnit, public IHasSide
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
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetTeam(int TeamNumber);
	void SetColor(FColor Color);
	
	virtual void MoveSelectedUnit(const FVector& GoalPosition, int Sender = -1) override;

	virtual void SelectUnit(AActor* SelectedUnit, ESelectStyle SelectionStyle) override;

	void SpawnEntities(const FTransform& SpawnLocation);

	virtual FSide GetSide() override;
};
