// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/BaseUnit.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/HasSide.h"
#include "Net/UnrealNetwork.h"
#include "ActorComponents/SelectionBox.h"
#include "Utils/ComponentUtils.h"


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

	// Subscribe for future updates & update to match existing state
	EntityInfo->RegisterSideUpdates(this, &ABaseUnit::OnSideChanged);
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseUnit::OnSideChanged(const FSide SideUpdate)
{
	const auto TeamMaterial = UMaterialInstanceDynamic::Create(BaseTeamMaterial, this);
	TeamMaterial->SetVectorParameterValue("TeamColor", SideUpdate.UnitColor);
	GetMesh()->SetMaterial(0, TeamMaterial);
}

