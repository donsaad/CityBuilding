#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableActor.generated.h"

enum class EPlacementState : uint8;

UCLASS()
class CITYBUILDING_API APlaceableActor : public AActor
{
	GENERATED_BODY()

public:

	APlaceableActor();
	APlaceableActor(const FObjectInitializer& ObjectInitializer);

	void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	bool CanBePlaced() const;
	void PlaceBuilding();
	void MarkAsBeingPlaced();
	bool IsPlaced() const;

protected:

	UPROPERTY(VisibleAnywhere)
		USceneComponent* DefaultSceneComp;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere)
		class UPlaceableBoxComponent* BoxCollision;

	EPlacementState BuildingState;

	UPROPERTY(EditDefaultsOnly)
		UMaterial* ValidPlacementMaterial;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* InvalidPlacementMaterial;

	virtual void BeginPlay() override;

};
