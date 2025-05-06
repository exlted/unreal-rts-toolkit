// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "BasicMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETURN_TO_THE_MAUL_API UBasicMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBasicMovementComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float RotationSpeed = 0.5;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
