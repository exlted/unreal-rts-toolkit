#pragma once
#include "SegmentTypes.h"

inline void DoSingleLineTrace(const UObject* WorldContext, FHitResult& Result, const UE::Geometry::TSegment3<double>& Line,
                              const ECollisionChannel Channel, const FCollisionQueryParams& Params)
{
	WorldContext->GetWorld()->LineTraceSingleByObjectType(Result, Line.Center, Line.EndPoint(), Channel, Params);
}

inline FHitResult DoSingleLineTrace(const UObject* WorldContext, const UE::Geometry::TSegment3<double>& Line,
	const ECollisionChannel Channel, const FCollisionQueryParams& Params)
{
	FHitResult Hit(ForceInit);
	DoSingleLineTrace(WorldContext, Hit, Line, Channel, Params);
	return Hit;
}

inline void DoSingleLineTrace(const UObject* WorldContext, FHitResult& Result, const UE::Geometry::TSegment3<double>& Line,
							  const FName Profile, const FCollisionQueryParams& Params)
{
	WorldContext->GetWorld()->LineTraceSingleByProfile(Result, Line.StartPoint(), Line.EndPoint(), Profile, Params);
}

inline FHitResult DoSingleLineTrace(const UObject* WorldContext, const UE::Geometry::TSegment3<double>& Line,
	const FName Profile, const FCollisionQueryParams& Params)
{
	FHitResult Hit(ForceInit);
	DoSingleLineTrace(WorldContext, Hit, Line, Profile, Params);
	return Hit;
}
