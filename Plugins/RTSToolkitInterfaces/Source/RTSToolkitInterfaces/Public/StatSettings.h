// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="Stat Settings"))
class RTSTOOLKITINTERFACES_API UStatSettings final : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UStatSettings() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Types")
	TArray<FString> StatTypes = {"Health", "Move Speed", "Defense"};

	UFUNCTION()
	static TArray<FString> GetStatTypes()
	{
		const auto StatSettings = GetDefault<UStatSettings>();
		
		return StatSettings->StatTypes;
	}
};