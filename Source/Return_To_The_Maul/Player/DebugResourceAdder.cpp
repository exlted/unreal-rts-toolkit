// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugResourceAdder.h"

#include "ActorComponents/PlayerEconomyManager.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UDebugResourceAdder::UDebugResourceAdder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UDebugResourceAdder::AddGold()
{
	if (const auto EconomyManager = GetRelatedSingletonTypedComponents<UPlayerEconomyManager>(GetOwner());
		EconomyManager != nullptr)
	{
		EconomyManager->AddToCurrentValue(FName("Gold"), 50);
	}
}

// Called when the game starts
void UDebugResourceAdder::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnDelegate.BindUFunction(this, FName("AddGold"));

	// Do this on the Client only
	if (GetWorld()->GetAuthGameMode() == nullptr)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(SpawnTimer, SpawnDelegate, 1.0, true);
	}
}


// Called every frame
void UDebugResourceAdder::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

