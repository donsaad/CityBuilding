
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CityGameModeBase.generated.h"

class APlaceableActor;

UCLASS()
class CITYBUILDING_API ACityGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACityGameModeBase(const FObjectInitializer& OI);
	void NotifyBuildingPlaced(const APlaceableActor* const NewlyPlacedBuilding);
	void NotifyVisitorReachedDestination(ACharacter* Visitor);

protected:

	TArray<const APlaceableActor*> PlacedBuildings;

	UPROPERTY(EditAnywhere, Category = "Visitor Settings")
		FVector VisitorSpawnLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Visitor Settings")
		float VisitorSpawnRate;
	UPROPERTY(EditDefaultsOnly, Category = "Visitor Settings")
		TSubclassOf<ACharacter> VisitorCharacterTemplate;
	TArray<ACharacter*> Visitors;

	FVector CachedLocSum;
	FVector MidPoint;

	virtual void BeginPlay() override;
	UFUNCTION()
		void SpawnVisitor();

};
