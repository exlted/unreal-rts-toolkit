// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Navigation.h"

#include "AIController.h"
#include "Components/SplineComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavFilters/NavigationQueryFilter.h"


// Sets default values for this component's properties
UNavigation::UNavigation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetAbsolute();
	Spline->ClearSplinePoints();
	DistanceToGoal = 0.0f;
	GoalDistanceThreshold = 100.0f;
	DistanceThreshold = 50.0f;
	// How many points are we setting between the start and end of the spline (0 -> 1)
	DistanceBetweenPoints = .01f;
}


// Called when the game starts
void UNavigation::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNavigation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	if (Spline->GetNumberOfSplinePoints() == 0)
	{
		return;
	}

	const FVector ActorLocation = GetOwner()->GetActorLocation();
	DistanceToGoal = (Goal - ActorLocation).Size2D();
	if (DistanceToGoal <= GoalDistanceThreshold)
	{
		Spline->ClearSplinePoints();
		return;
	}

	if (const float DistanceToNextPoint = (NextPoint - ActorLocation).Size2D(); DistanceToNextPoint <= DistanceThreshold)
	{
		CurrentTime += DistanceBetweenPoints;
		NextPoint = Spline->GetLocationAtTime(CurrentTime, ESplineCoordinateSpace::World);
	}

	const FVector Direction = (NextPoint - ActorLocation).GetSafeNormal2D();
	const FVector ActorDirection = GetOwner()->GetActorRotation().Vector().GetSafeNormal2D();
	const float Scale = FMath::Clamp(FVector::DotProduct(ActorDirection, Direction), 0.5f, 1.0f);
	Cast<APawn>(GetOwner())->AddMovementInput(Direction, Scale);
}

void UNavigation::MoveTo(const FVector& NewLocation)
{
	//Navigate(FindPathToLocation(NewLocation));
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(UAIBlueprintHelperLibrary::GetAIController(GetOwner()), NewLocation);
}

void UNavigation::MoveTo(AActor* NewTarget)
{
	UAIBlueprintHelperLibrary::SimpleMoveToActor(UAIBlueprintHelperLibrary::GetAIController(GetOwner()), NewTarget);
}

TArray<FVector> UNavigation::FindPathToLocation(const FVector& Location) const
{
	TArray<FVector> Result;
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (const APawn* Pawn = Cast<APawn>(GetOwner()); NavSys && Pawn)
	{
		FNavPathSharedPtr Path;
		if (const ANavigationData* NavData = NavSys->GetNavDataForProps(Pawn->GetNavAgentPropertiesRef(), Pawn->GetNavAgentLocation()))
		{
			const FSharedConstNavQueryFilter NavFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, this, nullptr);
			FPathFindingQuery Query = FPathFindingQuery(*Pawn, *NavData, Pawn->GetNavAgentLocation(), Location, NavFilter);
			Query.SetAllowPartialPaths(true);

			if (const FPathFindingResult PathResult = NavSys->FindPathSync(Query); PathResult.Result != ENavigationQueryResult::Error)
			{
				if (PathResult.IsSuccessful() && PathResult.Path.IsValid())
				{
					PathResult.Path->EnableRecalculationOnInvalidation(true);
					Path = PathResult.Path;
				}
			}
		}

		if (Path)
		{
			const TArray<FNavPathPoint>& Points = Path->GetPathPoints();
			for (int PointIndex = 0; PointIndex < Points.Num(); ++PointIndex)
			{
				Result.Add(Points[PointIndex].Location);
			}
		}
	}
	return Result;
}

void UNavigation::Navigate(const TArray<FVector>& Path)
{
	Spline->ClearSplinePoints();
	for (FVector Point : Path)
	{
		Spline->AddSplineWorldPoint(Point);
		Goal = Point;
	}
	Spline->Duration = 1.0f;
	CurrentTime = 0.0f;
	NextPoint = Spline->GetLocationAtTime(CurrentTime, ESplineCoordinateSpace::World);
	Length = Spline->GetSplineLength();
}

void UNavigation::Stop()
{
	Navigate(TArray<FVector>());
}

