// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/TurretController.h"
#include "RangeCollider.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API URangeCollider : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URangeCollider();

	UPROPERTY(EditAnywhere)
	TScriptInterface<ITurretController> Controller;

	UPROPERTY(EditAnywhere)
	TScriptInterface<ITargetable> TurretInfo;
	
	// For handling Target Acquisition
	UPROPERTY(EditAnywhere, meta = (UseComponentPicker))
	FComponentReference CollisionMeshReference;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ValidTargets;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
