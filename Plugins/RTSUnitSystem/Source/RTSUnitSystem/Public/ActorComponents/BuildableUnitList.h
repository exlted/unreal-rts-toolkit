// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Builder.h"
#include "Structs/Buildable.h"
#include "BuildableUnitList.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UBuildableUnitList : public UActorComponent, public IBuilder	
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBuildableUnitList();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBuildable> BuildableClasses;

	// Needs to know when we get selected & deselected to update UI
	// Needs to be able to talk with UI system so that it can fill out the buildable object list in the UI system
	// UI tells us to build - There will be a few types of BuildableUnitLists which handle the unit building in different ways
	// UI Manager
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual TArray<FBuildable> GetBuildableObjects() override;
	virtual void DisplayUI() override;
	virtual void HideUI() override;

	virtual void OnMenuItemClicked(UClass* SelectedClass) override;

private:
	APlayerState* GetPlayerState() const;
};
