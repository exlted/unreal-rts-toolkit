// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/SpawnLocation.h"


// Sets default values for this component's properties
USpawnLocation::USpawnLocation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnLocation::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpawnLocation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

