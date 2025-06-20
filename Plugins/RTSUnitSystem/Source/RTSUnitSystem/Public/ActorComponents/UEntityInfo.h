// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/FSide.h"
#include "Enums/EEntityType.h"
#include "Interfaces/Damagable.h"
#include "Interfaces/Spawnable.h"
#include "Interfaces/StatUpdater.h"
#include "Interfaces/Targetable.h"
#include "UEntityInfo.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UEntityInfo : public UActorComponent, public ITargetable, public ISpawnable, public IDamagable
	, public IStatUpdater
{
	GENERATED_BODY()
	
public:

	UEntityInfo();
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category=UnitInfo, ReplicatedUsing = OnRep_SideChanged)
	FSide SideInfo;

	UPROPERTY(Replicated, BlueprintReadOnly, Category=UnitInfo)
	FDataTableRowHandle TableRow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	FSideChanged OnSideChanged;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category=UnitInfo, ReplicatedUsing = OnRep_HealthChanged, meta=(AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category=UnitInfo, ReplicatedUsing = OnRep_HealthChanged, meta=(AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	TMap<EDamageSource, bool> Invulnerable;

	UPROPERTY()
	FStatUpdated OnStatUpdated;
	
	virtual void BeginPlay() override;
	
	bool FirstTick = false;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	std::vector<FName> GetTags() const;
	virtual FSide GetSide() override;
	virtual void SetSide(FSide NewSide) override;
	virtual void SetTableRow(const FDataTableRowHandle) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	virtual void OnRep_SideChanged();

	UFUNCTION()
	virtual void OnRep_HealthChanged();

	UFUNCTION()
	virtual void OnRep_MaxHealthChanged();

	virtual bool IsDamagableBy(EDamageSource Source) override;
	// returns true when dealt damage kills
	virtual bool DoDamage(float Amount) override;

	virtual void RegisterStatUpdatedCallback_Implementation(const FStatUpdatedParameter& CallbackFunc) override;
	virtual void DeregisterStatUpdatedCallback_Implementation(const FStatUpdatedParameter& CallbackFunc) override;
	virtual void InitializeCurrentState_Implementation(const FStatUpdatedParameter& CallbackFunc) override;
	
private:
	virtual FSideChanged& GetEventDelegate() override;
};
