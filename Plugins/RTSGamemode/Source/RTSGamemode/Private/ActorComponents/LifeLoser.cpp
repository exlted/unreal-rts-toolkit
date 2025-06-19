// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/LifeLoser.h"

#include "GameFramework/GameStateBase.h"
#include "Interfaces/LivesHandler.h"
#include "Utils/ComponentUtils.h"


// Sets default values for this component's properties
ULifeLoser::ULifeLoser()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULifeLoser::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionMesh == nullptr)
	{
		CollisionMesh = GetRelatedSingletonTypedComponents<UPrimitiveComponent>(GetOwner());
	}
	
	if (CollisionMesh != nullptr)
	{
		CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ULifeLoser::OverlapBegin);
	}
}


// Called every frame
void ULifeLoser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULifeLoser::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
	if (const auto GameState = GetWorld()->GetGameState();
		GameState != nullptr && GameState->Implements<ULivesHandler>())
	{
		const TScriptInterface<ILivesHandler> LivesHandler = GameState;
		LivesHandler->LoseLife();
	}
}

