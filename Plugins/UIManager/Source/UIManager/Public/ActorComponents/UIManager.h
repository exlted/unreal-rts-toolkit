// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUIComponent.h"
#include "Components/ActorComponent.h"
#include "Utils/ComponentUtils.h"
#include "UIManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UIMANAGER_API UUIManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUIManager();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	TWeakObjectPtr<UBaseUIComponent> GetComponentByName(FName Name) const;
	
	template<class BaseComponentType>
	TWeakObjectPtr<BaseComponentType> GetComponentByType()
	{
		TWeakObjectPtr<BaseComponentType> Return = nullptr;

		for (auto Components = GetRelatedTypedComponents<BaseComponentType>(GetOwner());
			auto Component : Components)
		{
			if (Return != nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Actor had more than 1 of an expected Singleton Component type"));
				break;
			}
			Return = Component;
		}
		
		return Return;
	}
	
	template<class Interface, class UInterface>
	TScriptInterface<Interface> GetComponentByInterface()
	{
		return GetRelatedSingletonComponent<Interface, UInterface>(GetOwner());
	}
	
};
