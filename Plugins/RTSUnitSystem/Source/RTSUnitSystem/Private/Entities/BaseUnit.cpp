// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/BaseUnit.h"

#include "Components/CapsuleComponent.h"


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

	EntityInfo = CreateDefaultSubobject<UEntityInfo>(TEXT("EntityInfo"));
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
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

void ABaseUnit::OnSelect()
{
	SelectionBox->SetVisibility(true, true);
}

void ABaseUnit::OnDeselect()
{
	SelectionBox->SetVisibility(false, true);
}

void ABaseUnit::MoveTo(const FVector& NewLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, NewLocation);
	//Navigation->Navigate(Navigation->FindPathToLocation(NewLocation));
}

FSide ABaseUnit::GetSide()
{
	return EntityInfo->SideInfo;
}

