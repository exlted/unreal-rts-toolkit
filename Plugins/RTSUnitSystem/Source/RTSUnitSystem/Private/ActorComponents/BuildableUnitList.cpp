// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/BuildableUnitList.h"

#include "GameFramework/PlayerState.h"
#include "Interfaces/BuilderUI.h"
#include "Interfaces/HasUIManager.h"


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

	// ...
	
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
				IBuilderUI::Execute_AddBuildableItems(BuilderUI.GetObject(), BuildableClasses);
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

APlayerState* UBuildableUnitList::GetPlayerState() const
{
	if (GetWorld() != nullptr && GetWorld()->GetFirstPlayerController() != nullptr)
	{
		return GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>();
	}

	return nullptr;
}

