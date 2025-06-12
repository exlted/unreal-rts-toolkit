// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/SelectionBox.h"

#include "ActorComponents/UEntityInfo.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/HasSide.h"
#include "Interfaces/UnitUI.h"
#include "Utils/ActorUtils.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
USelectionBox::USelectionBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;

	SetRelativeRotation(FRotator(0, 0, 90));
	DecalSize = FVector(10, 20, 20);
	SetRelativeLocation(FVector(0, 0, -30));
	SetVisibility(false);
}


// Called when the game starts
void USelectionBox::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(true);
	
	// ...
	TargetableComponent = GetRelatedSingletonComponent<ITargetable, UTargetable>(GetOwner());
	if (TargetableComponent != nullptr)
	{
		TargetableComponent->RegisterSideUpdates(this, &USelectionBox::OnSideChanged);
	}

	if (const auto EntityInfo = GetRelatedSingletonTypedComponents<UEntityInfo>(GetOwner());
		EntityInfo != nullptr)
	{
		AssociatedRow = EntityInfo->TableRow;
	}
}

void USelectionBox::SetDecalMaterial(UMaterialInstance* Material)
{
	if (Material != nullptr)
	{
		DecalMaterial = Material;
	}
}


void USelectionBox::UpdateTeamRelation()
{
	NeedRelationUpdate = true;

	if (TargetableComponent != nullptr)
	{
		if (const auto PlayerController = GetWorld()->GetFirstPlayerController(); PlayerController != nullptr)
		{
			if (const auto State = PlayerController->GetPlayerState<APlayerState>(); State != nullptr && State->Implements<UHasSide>())
			{
				if (const auto LocalPlayerSide = TScriptInterface<IHasSide>(State)->GetSide();
					LocalPlayerSide.Team == TargetableComponent->GetSide().Team) // Same Team
				{
					SetUnitRelation(EUnitRelationType::Owned);
				}
				else if (TargetableComponent->GetSide().Team == -1) // Unit Unowned
				{
					SetUnitRelation(EUnitRelationType::Neutral);
				}
				else
				{
					SetUnitRelation(EUnitRelationType::Enemy);
				}
				NeedRelationUpdate = false;
			}
		}
	}
}

// Called every frame
void USelectionBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (NeedRelationUpdate)
	{
		UpdateTeamRelation();
	}
}

void USelectionBox::SetUnitRelation(const EUnitRelationType Relation)
{
	switch (Relation)
	{
	case EUnitRelationType::Owned:
		SetDecalMaterial(OwnedUnit);
		break;
	case EUnitRelationType::Friendly:
		SetDecalMaterial(FriendlyUnit);
		break;
	case EUnitRelationType::Neutral:
		SetDecalMaterial(NeutralUnit);
		break;
	case EUnitRelationType::Enemy:
		SetDecalMaterial(EnemyUnit);
		break;
	case EUnitRelationType::Unset:
		break;
	}
}

void USelectionBox::OnSelect()
{
	SetVisibility(true);

	if (const auto State = GetPlayerState(GetOwner()).Pin();
		State != nullptr)
	{
		if (const auto UnitUI = GetRelatedSingletonComponent<IUnitUI, UUnitUI>(State.Get());
			UnitUI.GetObject() != nullptr)
		{
			IUnitUI::Execute_AddUnit(UnitUI.GetObject(), AssociatedRow);
		}
	}
}

void USelectionBox::OnDeselect()
{
	SetVisibility(false);
	
	if (const auto State = GetPlayerState(GetOwner()).Pin();
		State != nullptr)
	{
		if (const auto UnitUI = GetRelatedSingletonComponent<IUnitUI, UUnitUI>(State.Get());
			UnitUI.GetObject() != nullptr)
		{
			IUnitUI::Execute_RemoveUnit(UnitUI.GetObject(), AssociatedRow);
		}
	}
}

bool USelectionBox::HasTag(const FName TagName)
{
	return GetOwner()->Tags.Contains(TagName);
}

void USelectionBox::OnSideChanged(const FSide SideUpdate)
{
	UpdateTeamRelation();
}
