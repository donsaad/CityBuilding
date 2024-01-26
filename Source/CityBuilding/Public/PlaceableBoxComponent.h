
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PlaceableBoxComponent.generated.h"

UCLASS()
class CITYBUILDING_API UPlaceableBoxComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	// This is to override engine's behavior as we have all placeables set to overlap Pawn but we still want to affect pawn's navigation
	bool IsNavigationRelevant() const override;

};
