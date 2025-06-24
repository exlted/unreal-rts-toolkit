// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControlMapping.generated.h"

/**
 * 
 */
 USTRUCT(BlueprintType)
struct SIMPLEMENUSYSTEM_API FControlMapping : public FTableRowBase
{
	GENERATED_BODY()
 	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FKey MappedKey;

 	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(GetKeyOptions="ControlTypes.GetControlTypes"))
 	TMap<FName, UTexture2D*> TextureMap;
};
