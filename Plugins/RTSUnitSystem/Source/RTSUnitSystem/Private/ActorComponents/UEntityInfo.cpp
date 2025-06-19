// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/UEntityInfo.h"

#include "StatSettings.h"
#include "Net/UnrealNetwork.h"
#include "Structs/UnitInfo.h"

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

	switch (const auto Row = TableRow.GetRow<FUnitInfo>("Getting Associated Row");
		Row->Type)
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

void UEntityInfo::SetTableRow(const FDataTableRowHandle NewRowHandle)
{
	TableRow = NewRowHandle;
	const auto Row = TableRow.GetRow<FUnitInfo>("Getting Associated Row");
	if (const auto NewMaxHealth = Row->Stats.Find(UStatSettings::GetHealthStat());
		NewMaxHealth != nullptr)
	{
		const float HealthDelta = MaxHealth - Health;
		MaxHealth = *NewMaxHealth;
		OnStatUpdated.Broadcast(UStatSettings::GetHealthStat(), MaxHealth);
		Health = MaxHealth - HealthDelta;
		OnStatUpdated.Broadcast(UStatSettings::GetCurrentHealthStat(), Health);
		if (Health <= 0)
		{
			// I dunno... Should they die here? This really should only happen during initialization of a Unit
		}
	}
}

void UEntityInfo::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEntityInfo, SideInfo);
	DOREPLIFETIME(UEntityInfo, TableRow);
	DOREPLIFETIME(UEntityInfo, Health);
	DOREPLIFETIME(UEntityInfo, MaxHealth);
}

void UEntityInfo::OnRep_SideChanged()
{
	OnSideChanged.Broadcast(SideInfo);
}

void UEntityInfo::OnRep_HealthChanged()
{
	OnStatUpdated.Broadcast(UStatSettings::GetCurrentHealthStat(), Health);
}

void UEntityInfo::OnRep_MaxHealthChanged()
{
	OnStatUpdated.Broadcast(UStatSettings::GetHealthStat(), MaxHealth);
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

	OnStatUpdated.Broadcast(UStatSettings::GetCurrentHealthStat(), Health);
	
	if (Health <= 0)
	{
		GetOwner()->Destroy();
		return true;
	}
	return false;
}

void UEntityInfo::RegisterStatUpdatedCallback_Implementation(const FStatUpdatedParameter& CallbackFunc)
{
	OnStatUpdated.Add(CallbackFunc);
}

void UEntityInfo::DeregisterStatUpdatedCallback_Implementation(const FStatUpdatedParameter& CallbackFunc)
{
	OnStatUpdated.Remove(CallbackFunc);
}

void UEntityInfo::InitializeCurrentState_Implementation(const FStatUpdatedParameter& CallbackFunc)
{
	CallbackFunc.Execute(UStatSettings::GetCurrentHealthStat(), Health);
	CallbackFunc.Execute(UStatSettings::GetHealthStat(), MaxHealth);
}

FSideChanged& UEntityInfo::GetEventDelegate()
{
	return OnSideChanged;
}
