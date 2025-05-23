// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/PlayerControllerComponent.h"
#include "Interfaces/Spawner.h"
#include "BuildingMode.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTSPLAYERCONTROLLER_API UBuildingMode : public UActorComponent, public IPlayerControllerComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBuildingMode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* BuilderMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* RotateAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CancelClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* AddModifierAction;
	bool AddModifierPressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TScriptInterface<ISpawner> Spawner;

	UEnhancedInputLocalPlayerSubsystem*  EnhancedInputSubsystem;
	APlayerController* Controller;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool Enabled = false;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Enable() override;
	virtual void Disable() override;

	virtual void SetupInputComponent(UEnhancedInputLocalPlayerSubsystem* Subsystem,
		UEnhancedInputComponent* EnhancedInputComponent, APlayerController* PlayerController) override;

	virtual bool IsBaseController() override;
	virtual FName GetIdentifier() override;

	// Actions
	virtual void OnRotateTriggered(const FInputActionInstance& Instance);
	virtual void OnAddModifierTriggered(const FInputActionInstance& Instance);
	virtual void OnClickTriggered();
	virtual void OnCancelClickTriggered();
};
