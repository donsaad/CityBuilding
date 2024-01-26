
#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PlaceableStaticMeshComp.generated.h"

/**
 *
 */
UCLASS()
class CITYBUILDING_API UPlaceableStaticMeshComp : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// This is to override engine's behavior as we have all placeables set to overlap Pawn but we still want to affect navigation
	bool IsNavigationRelevant() const override;

};
