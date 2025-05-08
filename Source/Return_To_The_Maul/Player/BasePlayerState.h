// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/UnitSelectionSystem.h"
#include "ActorComponents/UnitSpawningSystem.h"
#include "GameFramework/PlayerState.h"
#include "Structs/FSide.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_TO_THE_MAUL_API ABasePlayerState : public APlayerState, public IMoveUnit, public ISelectUnit
{
	GENERATED_BODY()

	ABasePlayerState();
	
public:
	UPROPERTY(EditAnywhere)
	FSide Side;

	UPROPERTY(EditAnywhere)
	UUnitSelectionSystem* UnitSelectionSystem;

	UPROPERTY(EditAnywhere)
	UUnitSpawningSystem* UnitSpawningSystem;
	
	virtual void BeginPlay() override;
	
	virtual void MoveSelectedUnit(const FVector& GoalPosition) override;

	virtual void SelectUnit(AActor* SelectedUnit, ESelectStyle SelectionStyle) override;
};
