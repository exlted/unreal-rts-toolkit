// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Interfaces/Targetable.h"
#include "ActorComponents/UEntityInfo.h"
#include "BaseActor.generated.h"

UCLASS()
class RTSUNITSYSTEM_API ABaseActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UEntityInfo* EntityInfo;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnSelect();
	virtual void OnDeselect();
	virtual bool HasTag(FName TagName);
	
	virtual FSide GetSide();
};
