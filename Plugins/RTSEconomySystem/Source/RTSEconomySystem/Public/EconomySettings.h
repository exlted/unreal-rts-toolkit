// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EconomySettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="Economy Settings"))
class RTSECONOMYSYSTEM_API UEconomySettings final : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UEconomySettings() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EconomySettings")
	TArray<FString> ResourceTypes = {"Gold"};

	UFUNCTION()
	static TArray<FString> GetResourceTypes()
	{
		const auto EconomySettings = GetDefault<UEconomySettings>();
		
		return EconomySettings->ResourceTypes;
	}
};