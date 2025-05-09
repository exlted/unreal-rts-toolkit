// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActorComponents/Navigation.h"
#include "ActorComponents/SelectionBox.h"
#include "Interfaces/Movable.h"
#include "Interfaces/Selectable.h"
#include "Interfaces/Targetable.h"
#include "ActorComponents/UEntityInfo.h"
#include "Interfaces/Spawnable.h"
#include "BaseUnit.generated.h"

UCLASS()
class RTSUNITSYSTEM_API ABaseUnit : public ACharacter, public ISelectable, public IMovable, public ITargetable, public ISpawnable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* BaseTeamMaterial;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UNavigation* Navigation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USelectionBox* SelectionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UEntityInfo* EntityInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing = OnRep_SideChanged)
	FSide Side;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void OnSelect() override;
	virtual void OnDeselect() override;
	virtual bool HasTag(FName TagName) override;

	virtual void MoveTo(const FVector& NewLocation) override;

	virtual void SetSide(FSide NewSide) override;
	virtual FSide GetSide() override;

	UFUNCTION()
	virtual void OnRep_SideChanged();
};
