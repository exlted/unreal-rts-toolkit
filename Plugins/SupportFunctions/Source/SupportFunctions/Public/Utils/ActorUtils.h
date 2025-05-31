#pragma once
#include "CoreMinimal.h"
#include "ComponentUtils.h"

static TWeakObjectPtr<APlayerState> GetPlayerState(const AActor* WorldContext)
{
	if (WorldContext->GetWorld() != nullptr && WorldContext->GetWorld()->GetFirstPlayerController() != nullptr)
	{
		return WorldContext->GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>();
	}
	return nullptr;
}

template<class Interface, class UInterface>
static TScriptInterface<Interface> GetSingletonInterface(AActor* FromActor)
{
	if (FromActor == nullptr)
	{
		return nullptr;
	}

	TScriptInterface<Interface> Result = nullptr;
	
	if (FromActor->Implements<UInterface>())
	{
		Result = FromActor;
	}

	const auto Components = GetRelatedComponents<Interface, UInterface>(FromActor);
	if (Result != nullptr && Components.Num() > 0)
	{
		// Multiple components implement this supposedly singleton functionality!
		UE_LOG(LogTemp, Error, TEXT("Actor had more than 1 of an expected Singleton Component type"));
		return nullptr;
	}

	if (Result == nullptr)
	{
		if (Components.Num() > 1)
		{
			// Multiple components implement this supposedly singleton functionality!
			UE_LOG(LogTemp, Error, TEXT("Actor had more than 1 of an expected Singleton Component type"));
			return nullptr;
		}
		Result = Components[0];
	}
	
	
	return Result;
}

template<class Interface, class UInterface>
static TArray<TScriptInterface<Interface>> GetInterface(AActor* FromActor)
{
	
	if (FromActor == nullptr)
	{
		return nullptr;
	}

	TArray<TScriptInterface<Interface>> Result = GetRelatedComponents<Interface, UInterface>(FromActor);
	
	if (FromActor->Implements<UInterface>())
	{
		Result.Add(FromActor);
	}
	
	
	return Result;
}