// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/UEntityInfo.h"

#include "Net/UnrealNetwork.h"

UEntityInfo::UEntityInfo()
{
	SetIsReplicatedByDefault(true);
}

std::vector<FName> UEntityInfo::GetTags() const
{
	std::vector<FName> Tags;

	Tags.push_back(SideInfo.PlayerTag);

	switch (EntityType)
	{
	case EEntityType::Unit:
		Tags.push_back("Unit");
		break;
	case EEntityType::Building:
		Tags.push_back("Building");
		break;
	case EEntityType::Environment:
		Tags.push_back("Environment");
		break;
	default:
		Tags.push_back("Unknown");
		break;
	}
	
	return Tags;
}

FSide UEntityInfo::GetSide()
{
	return SideInfo;
}

void UEntityInfo::SetSide(const FSide NewSide)
{
	SideInfo = NewSide;
}

void UEntityInfo::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEntityInfo, SideInfo);
}

void UEntityInfo::OnRep_SideChanged()
{
	OnSideChanged.Broadcast(SideInfo);
}

FSideChanged& UEntityInfo::GetEventDelegate()
{
	return OnSideChanged;
}
