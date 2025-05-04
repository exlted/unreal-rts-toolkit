#pragma once
#include "CoreMinimal.h"

struct FLineSegment
{
	FVector Start;
	FVector End;
	
	FLineSegment(const FVector& Start, const FVector& End)
	{
		this->Start = Start;
		this->End = End;
	}

	FLineSegment(const FVector& Start, const FVector& Direction, const float Length)
	{
		this->Start = Start;
		this->End = Start + (Direction * Length);
	}
};
