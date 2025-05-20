// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/ModularPlayerController.h"
#include "Interfaces/PlayerControllerComponent.h"
#include "BasePlayerController.generated.h"

UCLASS()
class RTSPLAYERCONTROLLER_API ABasePlayerController : public APlayerController, public IModularPlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

	TArray<TScriptInterface<IPlayerControllerComponent>> Components;
	TMap<FName, TScriptInterface<IPlayerControllerComponent>> NamedComponents;
	TArray<TScriptInterface<IPlayerControllerComponent>> BaseComponents;

	TArray<TScriptInterface<IPlayerControllerComponent>> ComponentStack;
	
protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	
public:
	virtual TArray<FName> GetNamedComponents() override;
	virtual void PushNamedComponent(FName Name) override;
	virtual bool PopComponent() override;
};
