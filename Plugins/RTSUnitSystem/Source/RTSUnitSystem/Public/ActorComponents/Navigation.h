// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Movable.h"
#include "Navigation.generated.h"


class USplineComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSUNITSYSTEM_API UNavigation : public UActorComponent, public IMovable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UNavigation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* Spline;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void MoveTo(const FVector& NewLocation) override;
	virtual void MoveTo(AActor* NewTarget) override;
	
	UFUNCTION(BlueprintCallable)
	TArray<FVector> FindPathToLocation(const FVector& Location) const;
	
	UFUNCTION(BlueprintCallable)
	void Navigate(const TArray<FVector>& Path);

	UFUNCTION(BlueprintCallable)
	void Stop();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Goal;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector NextPoint;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DistanceToGoal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Length;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GoalDistanceThreshold = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceThreshold = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceBetweenPoints = 1.0f;
};
