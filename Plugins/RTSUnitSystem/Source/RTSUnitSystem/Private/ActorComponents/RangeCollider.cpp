// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/RangeCollider.h"

#include "Interfaces/Targetable.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
URangeCollider::URangeCollider()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URangeCollider::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Controller = GetRelatedSingletonComponent<ITurretController, UTurretController>(GetOwner());
	if (Controller != nullptr)
	{
		TurretInfo = GetRelatedSingletonComponent<ITargetable, UTargetable>(GetOwner());
		if (TurretInfo != nullptr)
		{
			if (const auto CollisionMesh = Cast<UPrimitiveComponent>(CollisionMeshReference.GetComponent(GetOwner()));
				CollisionMesh != nullptr)
			{
				CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &URangeCollider::OverlapBegin);
				CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &URangeCollider::OverlapEnd);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not find UPrimitiveComponent on Actor with URangeCollider."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not find ITargetable on Actor with URangeCollider."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find ITurretController on Actor with URangeCollider."));
	}
}

void URangeCollider::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (const auto CollisionMesh = Cast<UPrimitiveComponent>(CollisionMeshReference.GetComponent(GetOwner()));
		CollisionMesh != nullptr)
	{
		CollisionMesh->OnComponentBeginOverlap.RemoveDynamic(this, &URangeCollider::OverlapBegin);
		CollisionMesh->OnComponentEndOverlap.RemoveDynamic(this, &URangeCollider::OverlapEnd);
	}
}


// Called every frame
void URangeCollider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URangeCollider::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto Targetable = GetRelatedSingletonComponent<ITargetable, UTargetable>(OtherActor);
		Targetable != nullptr)
	{
		const auto OtherTeam = Targetable->GetSide().Team;
		const auto ThisTeam = TurretInfo->GetSide().Team;
		
		if (OtherTeam != ThisTeam)
		{
			// Check if the Actor can be attacked
			ValidTargets.AddUnique(OtherActor);
			Controller->SetCurrentTargetsInRange(ValidTargets);
		}
	}
}

void URangeCollider::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ValidTargets.Num() > 0)
	{
		if (const auto Index = ValidTargets.Find(OtherActor); Index != INDEX_NONE)
		{
			ValidTargets.RemoveAt(Index);
			Controller->SetCurrentTargetsInRange(ValidTargets);
		}
	}
}

