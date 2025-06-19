// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="Stat Settings"), BlueprintType)
class RTSTOOLKITINTERFACES_API UStatSettings final : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UStatSettings() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Types")
	TArray<FString> StatTypes = {"Health", "CurrentHealth", "Move Speed", "Defense"};

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Stat Names", meta=(GetOptions="GetStatTypes"))
	FString HealthStat;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Stat Names", meta=(GetOptions="GetStatTypes"))
	FString CurrentHealthStat;
	
	UFUNCTION(BlueprintCallable)
	static TArray<FString> GetStatTypes()
	{
		const auto StatSettings = GetDefault<UStatSettings>();
		return StatSettings->StatTypes;
	}

	UFUNCTION(BlueprintCallable)
	static FName GetHealthStat()
	{
		const auto StatSettings = GetDefault<UStatSettings>();
		return FName(StatSettings->HealthStat);
	}

	UFUNCTION(BlueprintCallable)
	static FName GetCurrentHealthStat()
	{
		const auto StatSettings = GetDefault<UStatSettings>();
		return FName(StatSettings->CurrentHealthStat);
	}
};