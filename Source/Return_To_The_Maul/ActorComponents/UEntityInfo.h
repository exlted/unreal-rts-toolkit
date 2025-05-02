// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Player/BasePlayerState.h"
#include "../Enums/EEntityType.h"
#include "UEntityInfo.generated.h"

UCLASS()
class RETURN_TO_THE_MAUL_API UEntityInfo : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	ABasePlayerState* PlayerInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	EEntityType EntityType;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	std::vector<FName> GetTags() const;
};
