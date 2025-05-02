// Fill out your copyright notice in the Description page of Project Settings.


#include "UEntityInfo.h"

std::vector<FName> UEntityInfo::GetTags() const
{
	std::vector<FName> Tags;

	if (PlayerInfo != nullptr)
	{
		Tags.push_back(PlayerInfo->PlayerTag);
	}

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

void UEntityInfo::BeginPlay()
{
	Super::BeginPlay();

	for (const auto Tags = GetTags(); const auto& Tag : Tags)
	{
		GetOwner()->Tags.Add(Tag);
	}
}
