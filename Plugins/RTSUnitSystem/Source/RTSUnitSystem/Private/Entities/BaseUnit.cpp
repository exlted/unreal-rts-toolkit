// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/BaseUnit.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/HasSide.h"
#include "Net/UnrealNetwork.h"


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
	SelectionBox = CreateDefaultSubobject<USelectionBox>(TEXT("SelectionBox"));
	SelectionBox->SetupAttachment(RootComponent);
	SelectionBox->SetVisibility(false, true);
	SelectionBox->SetRelativeRotation(FRotator(90, 0, 0));
	SelectionBox->SetRelativeLocation(FVector(0, 0, -30));

	EntityInfo = CreateDefaultSubobject<UEntityInfo>(TEXT("EntityInfo"));
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
	SelectionBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SelectionBox->SetVisibility(false, true);
	SelectionBox->SetRelativeRotation(FRotator(90, 0, 0));
	SelectionBox->SetRelativeLocation(FVector(0, 0, -30));
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

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseUnit::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseUnit, Side);
}

void ABaseUnit::OnSelect()
{
	SelectionBox->SetVisibility(true, true);
}

void ABaseUnit::OnDeselect()
{
	SelectionBox->SetVisibility(false, true);
}

bool ABaseUnit::HasTag(const FName TagName)
{
	return Tags.Contains(TagName);
}

void ABaseUnit::MoveTo(const FVector& NewLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, NewLocation);
	//Navigation->Navigate(Navigation->FindPathToLocation(NewLocation));
}

void ABaseUnit::SetSide(const FSide NewSide)
{
	EntityInfo->SideInfo = NewSide;
	Side = NewSide;
	
	for (const auto EntityInfoTags = EntityInfo->GetTags();
		const auto& Tag : EntityInfoTags)
	{
		Tags.AddUnique(Tag);
	}

	if (BaseTeamMaterial != nullptr)
	{
		const auto TeamMaterial = UMaterialInstanceDynamic::Create(BaseTeamMaterial, this);
		TeamMaterial->SetVectorParameterValue("TeamColor", NewSide.UnitColor);
		GetMesh()->SetMaterial(0, TeamMaterial);
	}
}

FSide ABaseUnit::GetSide()
{
	return Side;
}

void ABaseUnit::UpdateTeamRelation()
{
	NeedRelationUpdate = true;
	
	if (const auto PlayerController = GetWorld()->GetFirstPlayerController(); PlayerController != nullptr)
	{
		if (const auto State = PlayerController->GetPlayerState<APlayerState>(); State != nullptr && State->Implements<UHasSide>())
		{
			if (const auto LocalPlayerSide = TScriptInterface<IHasSide>(State)->GetSide();
				LocalPlayerSide.Team == Side.Team) // Same Team
			{
				SelectionBox->SetUnitRelation(EUnitRelationType::Owned);
			}
			else if (Side.Team == -1) // Unit Unowned
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

void ABaseUnit::OnRep_SideChanged()
{
	const auto TeamMaterial = UMaterialInstanceDynamic::Create(BaseTeamMaterial, this);
	TeamMaterial->SetVectorParameterValue("TeamColor", Side.UnitColor);
	GetMesh()->SetMaterial(0, TeamMaterial);

	
	UpdateTeamRelation();
}

