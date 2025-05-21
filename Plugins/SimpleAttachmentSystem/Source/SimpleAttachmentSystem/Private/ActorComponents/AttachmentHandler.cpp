// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AttachmentHandler.h"

#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
UAttachmentHandler::UAttachmentHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttachmentHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (const auto AttachmentPointComponents = GetRelatedTypedComponents<UAttachmentPoint>(GetOwner());
		const auto AttachmentPoint : AttachmentPointComponents)
	{
		FAttachmentInfo Info;
		Info.Name = AttachmentPoint->GetSlotName();
		Info.AttachmentPoint = AttachmentPoint;

		AttachmentPoints.Add(Info);
	}
}


TWeakObjectPtr<UAttachmentPoint> UAttachmentHandler::GetAttachment(const FName& Slot) const
{
	for (const auto [Name, AttachmentPoint] : AttachmentPoints)
	{
		if (Name == Slot)
		{
			if (AttachmentPoint.IsValid())
			{
				return AttachmentPoint;
			}
			return nullptr;
		}
	}
	

	return nullptr;
}

// Called every frame
void UAttachmentHandler::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FAttachmentInfo> UAttachmentHandler::GetAttachmentPoints() const
{
	return AttachmentPoints;
}

void UAttachmentHandler::AttachTo(const TWeakObjectPtr<AActor> ToAttach, const FName& Slot)
{
	if (const auto Attachment = GetAttachment(Slot); Attachment != nullptr)
	{
		Attachment.Pin()->AttachTo(ToAttach);
	}
}

void UAttachmentHandler::DetachFrom(const FName& Slot)
{
	if (const auto Attachment = GetAttachment(Slot); Attachment != nullptr)
	{
		Attachment.Pin()->DetachFrom();
	}
}

bool UAttachmentHandler::IsAttached(const FName& Slot) const
{
	if (const auto Attachment = GetAttachment(Slot); Attachment != nullptr)
	{
		return Attachment.Pin()->IsAttached();
	}
	return false;
}

