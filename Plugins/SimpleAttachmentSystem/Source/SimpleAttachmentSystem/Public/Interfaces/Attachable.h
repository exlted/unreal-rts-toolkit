// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/AttachmentInfo.h"
#include "UObject/Interface.h"
#include "Attachable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class SIMPLEATTACHMENTSYSTEM_API UAttachable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLEATTACHMENTSYSTEM_API IAttachable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TArray<FAttachmentInfo> GetAttachmentPoints() const = 0;
	virtual void AttachTo(TWeakObjectPtr<AActor> ToAttach, const FName& Slot) = 0;
	virtual void DetachFrom(const FName& Slot) = 0;
	virtual bool IsAttached(const FName& Slot) const = 0;
};
