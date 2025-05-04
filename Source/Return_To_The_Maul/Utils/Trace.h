#pragma once
#include "CoreMinimal.h"
#include "../Structs/FLineSegment.h"

inline void DoSingleLineTrace(const UObject* WorldContext, FHitResult& Result, const FLineSegment& Line,
	const ECollisionChannel Channel, const FCollisionQueryParams& Params)
{
	WorldContext->GetWorld()->LineTraceSingleByObjectType(Result, Line.Start, Line.End, Channel, Params);
}

inline FHitResult DoSingleLineTrace(const UObject* WorldContext, const FLineSegment& Line,
	const ECollisionChannel Channel, const FCollisionQueryParams& Params)
{
	FHitResult Hit(ForceInit);
	DoSingleLineTrace(WorldContext, Hit, Line, Channel, Params);
	return Hit;
}
