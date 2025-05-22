// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AttachmentPoint.h"


// Sets default values for this component's properties
UAttachmentPoint::UAttachmentPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttachmentPoint::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttachmentPoint::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FName UAttachmentPoint::GetSlotName() const
{
	return Name;
}

void UAttachmentPoint::SetSlotName(const FName NewName)
{
	Name = NewName;
}

void UAttachmentPoint::AttachTo(const TWeakObjectPtr<AActor> ToAttach)
{
	AttachedObject = ToAttach;

	if (AttachedObject.IsValid())
	{
		const auto Object = AttachedObject.Pin();
		Object->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	}
}

void UAttachmentPoint::DetachFrom()
{
	if (AttachedObject.IsValid())
	{
		const auto Object = AttachedObject.Pin();
		Object->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}
	AttachedObject.Reset();
}

bool UAttachmentPoint::IsAttached() const
{
	return AttachedObject.IsValid();
}

