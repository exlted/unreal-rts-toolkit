// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
enum RTSUNITSYSTEM_API ETurretState
{
	Idle, // When Idle, look for Target by Target Criteria. When Target Found, Transition to Firing
	Timeout, // Wait for specified Time Period, after Time Period, if Target Available, transition to Firing, else to Idle
	Firing, // Shoot target, transition into Timeout state. Theoretically, Target can change while in Firing state
};