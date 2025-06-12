// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/PlayerEconomyManager.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UPlayerEconomyManager::UPlayerEconomyManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	// ...
}


// Called when the game starts
void UPlayerEconomyManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerEconomyManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerEconomyManager::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayerEconomyManager, Resources);
}

void UPlayerEconomyManager::AddToCurrentValue(const FName ResourceName, const int AddedAmount)
{
	AddToCurrentValue_Internal(ResourceName, AddedAmount);
}

void UPlayerEconomyManager::AddToMaxValue(const FName ResourceName, const int AddedAmount)
{
	AddToMaxValue_Internal(ResourceName, AddedAmount);
}

int UPlayerEconomyManager::GetCurrentValue(const FName ResourceName) const
{
	for (auto& Resource : Resources)
	{
		if (Resource.Name == ResourceName)
		{
			return Resource.CurrentValue;
		}
	}
	return -1;
}

int UPlayerEconomyManager::GetMaxValue(const FName ResourceName) const
{
	for (auto& Resource : Resources)
	{
		if (Resource.Name == ResourceName)
		{
			return Resource.MaxValue;
		}
	}
	return -1;
}


void UPlayerEconomyManager::InitializeState()
{
	for (const auto& Resource : Resources)
	{
		OnResourceUpdated.Broadcast(Resource);
	}
}

void UPlayerEconomyManager::OnRep_ResourcesChanged(TArray<FResourceData> PreRepValue)
{
	TMap<FName, FResourceData> ResourceMap;

	for (const auto& Resource : PreRepValue)
	{
		ResourceMap.Add(Resource.Name, Resource);
	}

	for (const auto& Resource : Resources)
	{
		if (const auto UpdatedResource = ResourceMap.Find(Resource.Name);
			UpdatedResource != nullptr)
		{
			if (UpdatedResource->MaxValue != Resource.MaxValue
			 || UpdatedResource->CurrentValue != Resource.CurrentValue )
			{
				// Updated
				OnResourceUpdated.Broadcast(Resource);
			}
			ResourceMap.Remove(Resource.Name);
		}
		else
		{
			// Added
			OnResourceUpdated.Broadcast(Resource);
		}
	}

	for (auto& KeyVal : ResourceMap)
	{
		// Deleted
		KeyVal.Value.Deleted = true;
		OnResourceUpdated.Broadcast(KeyVal.Value);
	}
}

void UPlayerEconomyManager::AddToMaxValue_Internal_Implementation(const FName ResourceName, const int AddedAmount)
{
	for (auto& Resource : Resources)
	{
		if (Resource.Name == ResourceName)
		{
			Resource.MaxValue += AddedAmount;
			OnResourceUpdated.Broadcast(Resource);
			break;
		}
	}
}

void UPlayerEconomyManager::AddToCurrentValue_Internal_Implementation(const FName ResourceName, const int AddedAmount)
{
	for (auto& Resource : Resources)
	{
		if (Resource.Name == ResourceName)
		{
			Resource.CurrentValue += AddedAmount;
			OnResourceUpdated.Broadcast(Resource);
			break;
		}
	}
}

