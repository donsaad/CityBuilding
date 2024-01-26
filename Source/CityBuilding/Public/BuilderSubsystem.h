
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BuilderSubsystem.generated.h"

enum class EBuildingType : uint8;
class APlaceableActor;

UCLASS()
class CITYBUILDING_API UBuilderSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	// Begin FTickableGameObject
	UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }
	bool IsAllowedToTick() const override { return true; }
	void Tick(float DeltaTime) override;
	TStatId GetStatId() const override { return TStatId(); }
	// End FTickableGameObject

	UFUNCTION(BlueprintCallable)
		void TryPlaceBuilding(EBuildingType BuildingType);
	void CancelPlaceBuilding();
	void UpdatePlacement();
	void PlaceBuilding();
	bool IsPlacementModeEnabled() const { return bPlacementModeEnabled; }
protected:

	bool bPlacementModeEnabled;

	UPROPERTY()
		APlaceableActor* PlaceableActor;

};
