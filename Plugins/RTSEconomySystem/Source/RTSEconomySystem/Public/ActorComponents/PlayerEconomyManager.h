// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/ResourceData.h"
#include "PlayerEconomyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResourceUpdatedSignature, FResourceData, UpdatedResource);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSECONOMYSYSTEM_API UPlayerEconomyManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerEconomyManager();

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_ResourcesChanged)
	TArray<FResourceData> Resources;
	
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FResourceUpdatedSignature OnResourceUpdated;

	// Use Cases:
	// Enable/Disable Build Actions whether we can afford them or not
	// Future Considerations: Other Players should be able to see Economy Data of their allies in the Tab menu
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void AddToCurrentValue(const FName ResourceName, const int AddedAmount);
	UFUNCTION(BlueprintCallable)
	void AddToMaxValue(const FName ResourceName, const int AddedAmount);
	UFUNCTION(BlueprintCallable)
	int GetCurrentValue(const FName ResourceName) const;
	UFUNCTION(BlueprintCallable)
	int GetMaxValue(const FName ResourceName) const;

	UFUNCTION(BlueprintCallable)
	void InitializeState();
	
	UFUNCTION()
	virtual void OnRep_ResourcesChanged(TArray<FResourceData> PreRepValue);

protected:
	UFUNCTION(Server, Reliable)
	void AddToCurrentValue_Internal(const FName ResourceName, const int AddedAmount);
	UFUNCTION(Server, Reliable)
	void AddToMaxValue_Internal(const FName ResourceName, const int AddedAmount);
};
