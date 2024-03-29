
#include "PlaceableBoxComponent.h"
#include "PlaceableActor.h"

bool UPlaceableBoxComponent::IsNavigationRelevant() const
{
	if (APlaceableActor* PA = Cast<APlaceableActor>(GetOwner()))
	{
		if (PA->IsPlaced())
		{
			// if it is placed, make it affect navigation even tho we're not blocking Pawn
			return true;
		}
		return false;
	}
	return Super::IsNavigationRelevant();
}
