// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/UIManager.h"

#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UUIManager::UUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUIManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TWeakObjectPtr<UBaseUIComponent> UUIManager::GetComponentByName(const FName Name) const
{
	TWeakObjectPtr<UBaseUIComponent> Return = nullptr;

	for (auto Components = GetRelatedTypedComponents<UBaseUIComponent>(GetOwner());
		const auto Component : Components)
	{
		if (Component->UIName == Name)
		{
			if (Return != nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Actor had more than 1 of an expected Singleton Component type"));
				break;
			}
			Return = Component;
		}
	}
	
	return Return;
}

