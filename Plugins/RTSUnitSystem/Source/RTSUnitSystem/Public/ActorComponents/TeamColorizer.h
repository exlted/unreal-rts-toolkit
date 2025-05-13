// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Targetable.h"
#include "TeamColorizer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UTeamColorizer : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTeamColorizer();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* BaseTeamMaterial;
	
	UPROPERTY(EditAnywhere)
	TScriptInterface<ITargetable> TargetableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMeshComponent* MeshComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnSideChanged(const FSide SideUpdate);
};
