// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaypointNode.generated.h"

UCLASS()
class WAYPOINTSYSTEM_API AWaypointNode : public AActor
{
	GENERATED_BODY()

public:
	AWaypointNode();

	UPROPERTY(BlueprintReadOnly, Category = "WaypointNode", EditInstanceOnly)
	TWeakObjectPtr<AWaypointNode> PreviousNode;

	UPROPERTY(BlueprintReadOnly, Category = "WaypointNode", EditInstanceOnly)
	TWeakObjectPtr<AWaypointNode> NextNode;
	
	UPROPERTY(EditDefaultsOnly, Category = "WaypointNode")
	UPrimitiveComponent* CollisionMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
