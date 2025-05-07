// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/BaseActor.h"


// Sets default values
ABaseActor::ABaseActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EntityInfo = CreateDefaultSubobject<UEntityInfo>(TEXT("EntityInfo"));
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseActor::OnSelect()
{
}

void ABaseActor::OnDeselect()
{
}

FSide ABaseActor::GetSide()
{
	return EntityInfo->SideInfo;
}

