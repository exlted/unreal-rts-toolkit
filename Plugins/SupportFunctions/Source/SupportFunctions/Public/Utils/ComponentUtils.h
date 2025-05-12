// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


template<class Interface, class UInterface>
static TScriptInterface<Interface> GetRelatedSingletonComponent(AActor* FromActor)
{
	const auto Components = FromActor->GetComponentsByInterface(UInterface::StaticClass());

	if (Components.Num() > 0)
	{
		if (Components.Num() > 1)
		{
			// Multiple components implement this supposedly singleton functionality!
			UE_LOG(LogTemp, Error, TEXT("Actor had more than 1 of an expected Singleton Component type"));
			return nullptr;
		}
		return TScriptInterface<Interface>(Components[0]);
	}
		
	return nullptr;
}