// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/FSide.h"
#include "Enums/EEntityType.h"
#include "UEntityInfo.generated.h"

UCLASS()
class RTSUNITSYSTEM_API UEntityInfo : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	FSide SideInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UnitInfo, meta=(AllowPrivateAccess = "true"))
	EEntityType EntityType;

	std::vector<FName> GetTags() const;
};
