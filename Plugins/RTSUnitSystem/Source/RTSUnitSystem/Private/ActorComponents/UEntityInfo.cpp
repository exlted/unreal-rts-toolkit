// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/UEntityInfo.h"

#include "Net/UnrealNetwork.h"

UEntityInfo::UEntityInfo()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;

	for (int i = 0; i < static_cast<int>(EDamageSource::Count); i++)
	{
		Invulnerable.Add(FDamageSourceConstants::DamageSourceList[i], false);
	}
}

void UEntityInfo::BeginPlay()
{
	Super::BeginPlay();
	FirstTick = true;
	SetComponentTickEnabled(true);
}

void UEntityInfo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FirstTick)
	{
		FirstTick = false;
		OnRep_SideChanged();
	}
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

bool UEntityInfo::IsDamagableBy(const EDamageSource Source)
{
	if (Source == EDamageSource::Count)
	{
		UE_LOG(LogTemp, Error, TEXT("Damage Source was an invalid value (Count)"))
		return false;
	}
	
	if (Invulnerable.Contains(Source))
	{
		return !Invulnerable[Source];
	}
	// Default to vulnerable
	return true;
}

bool UEntityInfo::DoDamage(const float Amount)
{
	Health -= Amount;

	if (Health <= 0)
	{
		GetOwner()->Destroy();
		return true;
	}
	return false;
}

FSideChanged& UEntityInfo::GetEventDelegate()
{
	return OnSideChanged;
}
