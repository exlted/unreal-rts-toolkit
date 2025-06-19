// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/HealthBar.h"

#include "StatSettings.h"
#include "Interfaces/HealthBarUI.h"
#include "Interfaces/StatUpdater.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UHealthBar::UHealthBar()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthBar::BeginPlay()
{
	Super::BeginPlay();

	SetCastShadow(false);
	// ...
	if (!GetWidget()->Implements<UHealthBarUI>())
	{
		UE_LOG(LogTemp, Error, TEXT("Health Bar Widget is not a UHealthBarUI"));
	}
	else
	{
		HealthBar = GetWidget();
		if (const auto StatUpdater = GetRelatedSingletonComponent<IStatUpdater, UStatUpdater>(GetOwner());
			StatUpdater != nullptr)
		{
			HealthBar->Execute_RegisterStatUpdater(GetWidget(), StatUpdater);
		}
	}
}


// Called every frame
void UHealthBar::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
}

