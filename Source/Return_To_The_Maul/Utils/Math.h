#pragma once

static float RatioBetween(const float Start, const float End, const float Position)
{
	return fabs(End - Position) / fabs(End - Start);
}