// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControlTypes.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="Controller Types"), BlueprintType)
class SIMPLEMENUSYSTEM_API UControlTypes final : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UControlTypes() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controllers")
	TArray<FString> StatTypes = {"Mouse", "Keyboard", "Microsoft", "Sony", "Nintendo"};

	UFUNCTION(BlueprintCallable)
	static TArray<FString> GetControlTypes()
	{
		const auto StatSettings = GetDefault<UControlTypes>();
		return StatSettings->StatTypes;
	}
};
