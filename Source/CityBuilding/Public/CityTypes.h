#pragma once

#include "CityTypes.generated.h"

UENUM()
enum class EPlacementState : uint8
{
	NONE = 0,
	Created,
	BeingPlacedInvalid,
	BeingPlacedValid,
	Placed
};


UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	NONE = 0,
	Cube,
	Cone,
	Cylinder,
	Thing,
	House1,
	House2
	// etc..
};

UENUM()
enum class EBuilderMode : uint8
{
	NONE = 0,
	On,
	Off,
	// etc..
};

static FString GetEnumString(const FString& EnumName, const int32 Value)
{
	UEnum* Enum = FindFirstObjectSafe<UEnum>(*EnumName);
	return Enum ? Enum->GetNameStringByIndex(static_cast<uint8>(Value)) : TEXT("null");
}
