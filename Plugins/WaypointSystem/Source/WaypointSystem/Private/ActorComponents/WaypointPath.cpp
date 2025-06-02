// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/WaypointPath.h"


// Sets default values for this component's properties
UWaypointPath::UWaypointPath()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWaypointPath::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWaypointPath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FVector> UWaypointPath::GetPath()
{
	TArray<FVector> Path;

	if (FirstNode.IsValid())
	{
		auto CurrentNode = FirstNode.Pin();
		while (CurrentNode.IsValid())
		{
			Path.Add(CurrentNode->GetActorLocation());
			if (CurrentNode->NextNode.IsValid())
			{
				CurrentNode = CurrentNode->NextNode.Pin();
			}
			else
			{
				break;
			}
		}
	}

	return Path;
}

AActor* UWaypointPath::GetFirstNode()
{
	if (FirstNode.IsValid())
	{
		return FirstNode.Get();
	}
	return nullptr;
}

