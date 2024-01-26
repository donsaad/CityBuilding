
#include "BuilderSubsystem.h"
#include "PlaceableActor.h"
#include "CityGameInstance.h"
#include "CityGameModeBase.h"

void UBuilderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	bPlacementModeEnabled = false;
}

void UBuilderSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UBuilderSubsystem::Tick(float DeltaTime)
{
	if (bPlacementModeEnabled)
	{
		UpdatePlacement();
	}
}

void UBuilderSubsystem::TryPlaceBuilding(EBuildingType BuildingType)
{
	// TODO: update mesh only without spawning new actor
	if (bPlacementModeEnabled)
	{
		CancelPlaceBuilding();
	}
	if (UWorld* World = GetWorld())
	{
		if (UCityGameInstance* CGI = Cast<UCityGameInstance>(GetGameInstance()))
		{
			PlaceableActor = World->SpawnActorDeferred<APlaceableActor>(CGI->GetBuildingTemplate(BuildingType), FTransform());
			if (PlaceableActor)
			{
				PlaceableActor->MarkAsBeingPlaced();
				PlaceableActor->FinishSpawning(FTransform());
				bPlacementModeEnabled = true;
			}
		}
	}
}

void UBuilderSubsystem::CancelPlaceBuilding()
{
	bPlacementModeEnabled = false;
	if (PlaceableActor)
	{
		PlaceableActor->Destroy();
	}
}

void UBuilderSubsystem::UpdatePlacement()
{
	if (!PlaceableActor)
		return;
	if (UGameInstance* GI = GetGameInstance())
	{
		if (APlayerController* PC = GI->GetFirstLocalPlayerController())
		{
			FVector WorldLoc, WorldDir;
			if (PC->DeprojectMousePositionToWorld(WorldLoc, WorldDir))
			{
				FHitResult HitResult;
				FCollisionQueryParams QueryParams;
				QueryParams.AddIgnoredActor(PC);
				GetWorld()->LineTraceSingleByChannel(HitResult, WorldLoc, WorldLoc + (WorldDir * 30000.0f), ECollisionChannel::ECC_GameTraceChannel1, QueryParams);
				if (HitResult.bBlockingHit)
				{
					PlaceableActor->SetActorLocation(HitResult.Location);
				}
			}
		}
	}
}

void UBuilderSubsystem::PlaceBuilding()
{
	if (bPlacementModeEnabled && PlaceableActor && PlaceableActor->CanBePlaced())
	{
		bPlacementModeEnabled = false;
		PlaceableActor->PlaceBuilding();
		// notify authority GM
		if (UWorld* World = GetWorld())
		{
			if (ACityGameModeBase* GM = World->GetAuthGameMode<ACityGameModeBase>())
			{
				GM->NotifyBuildingPlaced(PlaceableActor);
			}
		}
	}
}
