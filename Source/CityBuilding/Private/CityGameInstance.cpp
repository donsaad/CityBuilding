#include "CityGameInstance.h"

TSubclassOf<APlaceableActor> UCityGameInstance::GetBuildingTemplate(const EBuildingType BuildingType) const
{
	if (BuildingTemplates.Contains(BuildingType))
	{
		return BuildingTemplates[BuildingType];
	}
	return DefaultBuildingTemplate;
}

void UCityGameInstance::GetAvailableBuildingTypes(TArray<EBuildingType>& OutBuildingTypes)
{
	OutBuildingTypes.Reserve(BuildingTemplates.Num());
	for (const auto& P : BuildingTemplates)
	{
		OutBuildingTypes.Add(P.Key);
	}
}
