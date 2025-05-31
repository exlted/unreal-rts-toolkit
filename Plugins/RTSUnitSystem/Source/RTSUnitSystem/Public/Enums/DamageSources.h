// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EDamageSource
{
	Projectile,
	Creep,
	Count
};

struct FDamageSourceConstants
{
	static constexpr EDamageSource DamageSourceList[] {
		EDamageSource::Projectile,
		EDamageSource::Creep
	};
};