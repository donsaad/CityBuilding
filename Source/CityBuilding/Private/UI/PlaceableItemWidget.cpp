
#include "UI/PlaceableItemWidget.h"
#include "Components/Button.h"
#include <Components/TextBlock.h>
#include "../../Public/BuilderSubsystem.h"
#include "CityTypes.h"

UPlaceableItemWidget::UPlaceableItemWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ItemType(EBuildingType::NONE)
{

}

void UPlaceableItemWidget::SetType(const EBuildingType BuildingType)
{
	ItemType = BuildingType;
}

void UPlaceableItemWidget::NativeConstruct()
{
	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UPlaceableItemWidget::ItemButtonClicked);
	}
	if (ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(GetEnumString("EBuildingType", (int32)ItemType)));
	}
	Super::NativeConstruct();
}

void UPlaceableItemWidget::ItemButtonClicked()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBuilderSubsystem* Builder = GI->GetSubsystem<UBuilderSubsystem>())
		{
			Builder->TryPlaceBuilding(ItemType);
		}
	}
}
