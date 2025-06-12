// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/BuildableUnitList.h"

#include "ActorComponents/PlayerEconomyManager.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/BuilderUI.h"
#include "Interfaces/HasUIManager.h"
#include "Interfaces/Spawner.h"


// Sets default values for this component's properties
UBuildableUnitList::UBuildableUnitList()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildableUnitList::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBuildableUnitList::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FBuildable> UBuildableUnitList::GetBuildableObjects()
{
	return BuildableClasses;
}

void UBuildableUnitList::DisplayUI()
{
	if (const auto PlayerState = GetPlayerState(); PlayerState && PlayerState->Implements<UHasUIManager>())
	{
		if (const auto UIManager = Cast<IHasUIManager>(PlayerState)->GetUIManager();
			UIManager.IsValid())
		{
			const auto BuilderUI = UIManager->GetComponentByInterface<IBuilderUI, UBuilderUI>();
			if (BuilderUI.GetObject() != nullptr)
			{
				IBuilderUI::Execute_AddBuildableItems(BuilderUI.GetObject(), BuildableClasses, this);
			}
		}
	}
}

void UBuildableUnitList::HideUI()
{
	if (const auto PlayerState = GetPlayerState(); PlayerState && PlayerState->Implements<UHasUIManager>())
	{
		if (const auto UIManager = Cast<IHasUIManager>(PlayerState)->GetUIManager();
			UIManager.IsValid())
		{
			if (const auto BuilderUI = UIManager->GetComponentByInterface<IBuilderUI, UBuilderUI>();
				BuilderUI.GetObject() != nullptr)
			{
				IBuilderUI::Execute_ClearBuildableItems(BuilderUI.GetObject());
			}
		}
	}
}

void UBuildableUnitList::OnMenuItemClicked_Implementation(const FBuildable& RequestedItem)
{
	const auto UnitInfo = RequestedItem.UnitInfo.GetRow<FUnitInfo>("RequestedToBuild");
	
	if (const auto PlayerState = GetPlayerState(); PlayerState != nullptr)
	{
		//TODO: This needs to be reworked so that it only pays the cost after the player completes the action
		if (const auto EconomyManager = GetRelatedSingletonTypedComponents<UPlayerEconomyManager>(PlayerState);
			EconomyManager != nullptr)
		{
			TArray<FResourceCost> AppliedCosts;
			
			
			for (const auto& Cost : UnitInfo->Cost)
			{
				if (EconomyManager->GetCurrentValue(Cost.Resource) > Cost.Cost)
				{
					AppliedCosts.Add(Cost);
					EconomyManager->AddToCurrentValue(Cost.Resource, Cost.Cost * -1);
				}
				else
				{
					break;
				}
			}
			
			if (UnitInfo->Cost.Num() > AppliedCosts.Num())
			{
				// Failed to apply all costs, revert and return;
				for (const auto& [Resource, Cost] : AppliedCosts)
				{
					EconomyManager->AddToCurrentValue(Resource, Cost);
				}
				
				return;
			}
		}
		
		if (const auto SpawningSystem = GetRelatedSingletonComponent<ISpawner, USpawner>(PlayerState);
			SpawningSystem.GetObject() != nullptr)
		{
			FTransform SpawnTransform = GetOwner()->GetActorTransform();
			SpawnTransform.AddToTranslation(GetOwner()->GetActorForwardVector() * 10);

			if (RequestedItem.PlayerDefinedLocation)
			{
				SpawningSystem->SpawnPlayerDefinedEntity(this, RequestedItem.UnitInfo);
			}
			else
			{
				SpawningSystem->SpawnEntity(this, RequestedItem.UnitInfo, SpawnTransform);
			}
		}
	}
}

APlayerState* UBuildableUnitList::GetPlayerState() const
{
	if (GetWorld() != nullptr && GetWorld()->GetFirstPlayerController() != nullptr)
	{
		return GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>();
	}

	return nullptr;
}

