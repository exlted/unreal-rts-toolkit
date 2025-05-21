#pragma once
#include "ActorComponents/AttachmentPoint.h"
#include "AttachmentInfo.generated.h"

USTRUCT(BlueprintType)
struct SIMPLEATTACHMENTSYSTEM_API FAttachmentInfo
{
	GENERATED_BODY()
	
	FName Name;
	TWeakObjectPtr<UAttachmentPoint> AttachmentPoint; 
};
