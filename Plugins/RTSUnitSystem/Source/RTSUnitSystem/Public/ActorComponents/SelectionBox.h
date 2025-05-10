// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/DecalComponent.h"
#include "Enums/UnitRelationType.h"
#include "SelectionBox.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API USelectionBox : public UDecalComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USelectionBox();

	UPROPERTY(EditAnywhere)
	UMaterialInstance* OwnedUnit;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* FriendlyUnit;
	
	UPROPERTY(EditAnywhere)
	UMaterialInstance* NeutralUnit;
	
	UPROPERTY(EditAnywhere)
	UMaterialInstance* EnemyUnit;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetUnitRelation(EUnitRelationType Relation);
};
