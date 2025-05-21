// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Attachable.h"
#include "AttachmentHandler.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEATTACHMENTSYSTEM_API UAttachmentHandler : public UActorComponent, public IAttachable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAttachmentHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	TArray<FAttachmentInfo> AttachmentPoints;

	TWeakObjectPtr<UAttachmentPoint> GetAttachment(const FName& Slot) const;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual TArray<FAttachmentInfo> GetAttachmentPoints() const override;
	virtual void AttachTo(TWeakObjectPtr<AActor> ToAttach, const FName& Slot) override;
	virtual void DetachFrom(const FName& Slot) override;
	virtual bool IsAttached(const FName& Slot) const override;
};
