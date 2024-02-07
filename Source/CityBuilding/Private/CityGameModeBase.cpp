
#include "CityGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlaceableActor.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "VisitorAIController.h"

ACityGameModeBase::ACityGameModeBase(const FObjectInitializer& OI) : Super(OI)
{
	VisitorSpawnRate = 3.0f;
	MidPoint = FVector::ZeroVector;
}

void ACityGameModeBase::NotifyBuildingPlaced(APlaceableActor* const NewlyPlacedBuilding)
{
	if (!NewlyPlacedBuilding)
	{
		UE_LOG(LogTemp, Error, TEXT("ACityGameModeBase::NotifyBuildingPlaced Error "));
		return;
	}

	// save to current list
	PlacedBuildings.Add(NewlyPlacedBuilding);

	// update midpoint
	CachedLocSum += NewlyPlacedBuilding->GetActorLocation();
	MidPoint = CachedLocSum / PlacedBuildings.Num();
	// update visitors destination
	for (ACharacter* V : Visitors)
	{
		if (V)
		{
			if (AVisitorAIController* AIC = V->GetController<AVisitorAIController>())
			{
				if (UBlackboardComponent* BBComp = AIC->GetBlackboardComponent())
				{
					BBComp->SetValueAsVector("MidpointLocation", MidPoint);
					break; // since it's instanced key we can break at first valid visitor
				}
			}
		}
	}
}

void ACityGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlacedBuildings.Reserve(10);

	FTimerHandle TempTimerHandle;
	GetWorldTimerManager().SetTimer(TempTimerHandle, this, &ACityGameModeBase::SpawnVisitor, VisitorSpawnRate, true);

}

void ACityGameModeBase::SpawnVisitor()
{
	if (UWorld* World = GetWorld())
	{
		ACharacter* Visitor = World->SpawnActor<ACharacter>(VisitorCharacterTemplate, VisitorSpawnLocation, FRotator::ZeroRotator);
		if (Visitor)
		{
			Visitors.Add(Visitor);
			if (AVisitorAIController* AIC = Visitor->GetController<AVisitorAIController>())
			{
				if (UBlackboardComponent* BBComp = AIC->GetBlackboardComponent())
				{
					BBComp->SetValueAsVector("MidpointLocation", MidPoint);
				}
			}
		}
	}
}

void ACityGameModeBase::NotifyVisitorReachedDestination(ACharacter* Visitor)
{
	if (Visitor)
	{
		Visitors.RemoveSwap(Visitor, false);
		Visitor->Destroy();
	}
}
