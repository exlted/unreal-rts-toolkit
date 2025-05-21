// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttachmentPoint.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEATTACHMENTSYSTEM_API UAttachmentPoint : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAttachmentPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FName Name;

	TWeakObjectPtr<AActor> AttachedObject;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	FName GetSlotName() const;
	
	virtual void AttachTo(TWeakObjectPtr<AActor> ToAttach);
	virtual void DetachFrom();
	virtual bool IsAttached() const;
};
