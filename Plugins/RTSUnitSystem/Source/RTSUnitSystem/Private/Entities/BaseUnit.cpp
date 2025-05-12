// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/BaseUnit.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/HasSide.h"
#include "Net/UnrealNetwork.h"
#include "ActorComponents/SelectionBox.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Update Sane Defaults
	GetMesh()->SetReceivesDecals(false);
	GetCapsuleComponent()->SetCapsuleHalfHeight(30, true);
	GetCapsuleComponent()->SetCapsuleRadius( 10, true);
	
	Navigation = CreateDefaultSubobject<UNavigation>(TEXT("Navigation"));

	EntityInfo = CreateDefaultSubobject<UEntityInfo>(TEXT("EntityInfo"));
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
	const auto Selectables = GetComponentsByInterface(USelectable::StaticClass());
	if (Selectables.Num() > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Implements more than 1 component that implements ISelectable"));
	}
	for (const auto& Selectable : Selectables)
	{
		SelectableComponent = Selectable;
	}

	// Subscribe for future updates & update to match existing state
	EntityInfo->RegisterSideUpdates(this, &ABaseUnit::OnSideChanged);
	OnSideChanged(EntityInfo->GetSide());
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (NeedRelationUpdate)
	{
		UpdateTeamRelation();
	}
}

void ABaseUnit::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseUnit, EntityInfo);
}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseUnit::UpdateTeamRelation()
{
	NeedRelationUpdate = true;

	if (SelectableComponent != nullptr && SelectableComponent.GetObject()->IsA(USelectionBox::StaticClass()))
	{
		const auto SelectionBox = Cast<USelectionBox>(SelectableComponent.GetObject());
		if (const auto PlayerController = GetWorld()->GetFirstPlayerController(); PlayerController != nullptr)
		{
			if (const auto State = PlayerController->GetPlayerState<APlayerState>(); State != nullptr && State->Implements<UHasSide>())
			{
				if (const auto LocalPlayerSide = TScriptInterface<IHasSide>(State)->GetSide();
					LocalPlayerSide.Team == EntityInfo->GetSide().Team) // Same Team
				{
					SelectionBox->SetUnitRelation(EUnitRelationType::Owned);
				}
				else if (EntityInfo->GetSide().Team == -1) // Unit Unowned
				{
					SelectionBox->SetUnitRelation(EUnitRelationType::Neutral);
				}
				else
				{
					SelectionBox->SetUnitRelation(EUnitRelationType::Enemy);
				}
				NeedRelationUpdate = false;
			}
		}
	}
}

void ABaseUnit::OnSideChanged(const FSide SideUpdate)
{
	const auto TeamMaterial = UMaterialInstanceDynamic::Create(BaseTeamMaterial, this);
	TeamMaterial->SetVectorParameterValue("TeamColor", SideUpdate.UnitColor);
	GetMesh()->SetMaterial(0, TeamMaterial);

	UpdateTeamRelation();
}

