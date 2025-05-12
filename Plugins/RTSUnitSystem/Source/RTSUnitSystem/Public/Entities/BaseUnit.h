// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActorComponents/Navigation.h"
#include "Interfaces/Selectable.h"
#include "ActorComponents/UEntityInfo.h"
#include "BaseUnit.generated.h"

UCLASS()
class RTSUNITSYSTEM_API ABaseUnit : public ACharacter
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

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UEntityInfo* EntityInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TScriptInterface<ISelectable> SelectableComponent;

	bool NeedRelationUpdate = false;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void UpdateTeamRelation();

	UFUNCTION()
	virtual void OnSideChanged(FSide SideUpdate);
};
