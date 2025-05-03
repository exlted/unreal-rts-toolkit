// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Navigation.generated.h"


class USplineComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETURN_TO_THE_MAUL_API UNavigation : public UActorComponent
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
	
	UFUNCTION(BlueprintCallable)
	TArray<FVector> FindPathToLocation(const FVector& Location);
	
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
	float GoalDistanceThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceBetweenPoints;
};
