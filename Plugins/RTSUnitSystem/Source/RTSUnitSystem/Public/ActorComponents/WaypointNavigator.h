// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Movable.h"
#include "Interfaces/WaypointFollower.h"
#include "WaypointNavigator.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UWaypointNavigator : public UActorComponent, public IWaypointFollower, public IMovable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWaypointNavigator();

	UPROPERTY(EditAnywhere)
	AActor* CurrentTarget;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void MoveTo(const FVector& NewLocation);
	virtual void MoveTo(AActor* NewTarget);
	
	virtual AActor* GetCurrentTarget() override;
	virtual void SetNewTarget(AActor* NewTarget) override;
};
