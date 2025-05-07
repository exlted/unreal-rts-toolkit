// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/BaseUnit.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Navigation = CreateDefaultSubobject<UNavigation>(TEXT("Navigation"));
	SelectionBox = CreateDefaultSubobject<USelectionBox>(TEXT("SelectionBox"));
	SelectionBox->SetupAttachment(RootComponent);
	SelectionBox->SetHiddenInGame(true, true);

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
	SelectionBox->SetHiddenInGame(false, true);
}

void ABaseUnit::OnDeselect()
{
	SelectionBox->SetHiddenInGame(true, true);
}

void ABaseUnit::MoveTo(const FVector& NewLocation)
{
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), NewLocation);
	Navigation->Navigate(Navigation->FindPathToLocation(NewLocation));
}

FSide ABaseUnit::GetSide()
{
	return EntityInfo->SideInfo;
}

