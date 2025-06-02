// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/WaypointNavigator.h"

#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


// Sets default values for this component's properties
UWaypointNavigator::UWaypointNavigator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWaypointNavigator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWaypointNavigator::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWaypointNavigator::MoveTo(const FVector& NewLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(UAIBlueprintHelperLibrary::GetAIController(GetOwner()), NewLocation);
}

void UWaypointNavigator::MoveTo(AActor* NewTarget)
{
	SetNewTarget(NewTarget);
}

AActor* UWaypointNavigator::GetCurrentTarget()
{
	return CurrentTarget;
}

void UWaypointNavigator::SetNewTarget(AActor* NewTarget)
{
	CurrentTarget = NewTarget;
	
	UAIBlueprintHelperLibrary::SimpleMoveToActor(UAIBlueprintHelperLibrary::GetAIController(GetOwner()), NewTarget);
}

