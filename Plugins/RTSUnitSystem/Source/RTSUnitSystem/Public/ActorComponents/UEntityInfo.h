// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/FSide.h"
#include "Enums/EEntityType.h"
#include "Interfaces/Spawnable.h"
#include "Interfaces/Targetable.h"
#include "UEntityInfo.generated.h"

UCLASS()
class RTSUNITSYSTEM_API UEntityInfo : public UActorComponent, public ITargetable, public ISpawnable
{
	GENERATED_BODY()
	
public:

	UEntityInfo();
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"), ReplicatedUsing = OnRep_SideChanged)
	FSide SideInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	EEntityType EntityType;

	UPROPERTY()
	FSideChanged OnSideChanged;
	
	std::vector<FName> GetTags() const;
	virtual FSide GetSide() override;
	virtual void SetSide(FSide NewSide) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	virtual void OnRep_SideChanged();
	
private:
	virtual FSideChanged GetEventDelegate() override;
};
