// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/MoveUnit.h"
#include "Interfaces/SelectUnit.h"
#include "Structs/FSelected.h"
#include "UnitSelectionSystem.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UUnitSelectionSystem : public UActorComponent, public IMoveUnit, public ISelectUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUnitSelectionSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<FSelected> SelectedUnits;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void MoveSelectedUnit(const FVector& GoalPosition) override;

	virtual void SelectUnit(AActor* SelectedUnit, ESelectStyle SelectionStyle) override;
	virtual TArray<FSelected> GetSelectedUnits();

	// Server Functions
	UFUNCTION(Server, Reliable)
	virtual void MoveUnits(const TArray<FSelected>& Units, const FVector& GoalPosition);
};
