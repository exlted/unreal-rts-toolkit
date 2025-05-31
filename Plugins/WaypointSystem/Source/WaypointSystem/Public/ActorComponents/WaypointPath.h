// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/WaypointNode.h"
#include "Components/ActorComponent.h"
#include "Interfaces/WaypointHolder.h"
#include "WaypointPath.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WAYPOINTSYSTEM_API UWaypointPath : public UActorComponent, public IWaypointHolder
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWaypointPath();
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "WaypointNode")
	TWeakObjectPtr<AWaypointNode> FirstNode;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual TArray<FVector> GetPath() override;
};
