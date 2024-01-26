
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CityGameInstance.generated.h"

enum class EBuildingType : uint8;
class APlaceableActor;

UCLASS()
class CITYBUILDING_API UCityGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	TSubclassOf<APlaceableActor> GetBuildingTemplate(const EBuildingType BuildingType) const;
	UFUNCTION(BlueprintCallable)
		void GetAvailableBuildingTypes(TArray<EBuildingType>& OutBuildingTypes);
protected:

	UPROPERTY(EditDefaultsOnly)
		TMap<EBuildingType, TSubclassOf<APlaceableActor>> BuildingTemplates;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<APlaceableActor> DefaultBuildingTemplate;
};
