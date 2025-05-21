// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseUIComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEUIMANAGER_API UBaseUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseUIComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName UIName = "Unset";
};
