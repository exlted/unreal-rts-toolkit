// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/BasicMovementComponent.h"


// Sets default values for this component's properties
UBasicMovementComponent::UBasicMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBasicMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBasicMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (const auto Pawn = Cast<APawn>(GetOwner()); Pawn != nullptr)
	{
		if (const auto MovementVector = Pawn->ConsumeMovementInputVector(); MovementVector != FVector::ZeroVector)
		{
			const auto Location = Pawn->GetActorLocation();

			// Move From ActorLocation towards MovementInputVector, but first we have to orient towards the direction we'll move in
			

			if (const auto Forward = Pawn->GetActorForwardVector();
				FMath::IsNearlyEqual(MovementVector.HeadingAngle(), Forward.HeadingAngle(), 1))
			{
				Pawn->SetActorLocation(Location + MovementVector);
				Pawn->SetActorRotation(MovementVector.Rotation());
			}
			else
			{
				Pawn->SetActorRotation(FMath::RInterpTo(Forward.Rotation(), MovementVector.Rotation(), DeltaTime, RotationSpeed));
			}

		}
	}
}

