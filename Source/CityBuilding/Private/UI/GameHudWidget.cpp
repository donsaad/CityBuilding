
#include "UI/GameHudWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "../../Public/CityHUD.h"
#include "CityGameInstance.h"
#include "CityTypes.h"
#include "UI/PlaceableItemWidget.h"

UGameHudWidget::UGameHudWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, GameHud(nullptr)
{
}

void UGameHudWidget::NativeConstruct()
{
	if (OpenPlacementUIBtn)
	{
		OpenPlacementUIBtn->OnClicked.AddDynamic(this, &UGameHudWidget::OpenPlacementUIBtnClicked);
	}
	if (APlayerController* PC = GetOwningPlayer())
	{
		GameHud = PC->GetHUD<ACityHUD>();
	}
	PlaceablesScrollBox->ClearChildren();
	if (UCityGameInstance* GI = GetGameInstance<UCityGameInstance>())
	{
		TArray<EBuildingType> AvailableBuildings;
		GI->GetAvailableBuildingTypes(AvailableBuildings);
		UPlaceableItemWidget* ItemWidget = nullptr;
		for (EBuildingType& Building : AvailableBuildings)
		{
			ItemWidget = CreateWidget<UPlaceableItemWidget>(GetOwningPlayer(), PlaceableItemWidgetTemplate);
			if (ItemWidget)
			{
				ItemWidget->SetType(Building);
				PlaceablesScrollBox->AddChild(ItemWidget);
			}
		}
	}
	Super::NativeConstruct();
}

void UGameHudWidget::OpenPlacementUIBtnClicked()
{
	TogglePlacementUI(true);
}

void UGameHudWidget::TogglePlacementUI(const bool bOpen)
{
	OpenPlacementUIBtn->SetIsEnabled(!bOpen);
	PlayAnimation(FadeOutOpenPlacementBtn, 0.0f, 1, (bOpen ? EUMGSequencePlayMode::Forward : EUMGSequencePlayMode::Reverse), 4.0f);
	PlayAnimation(FadeInPlacementUI, 0.0f, 1, (bOpen ? EUMGSequencePlayMode::Forward : EUMGSequencePlayMode::Reverse), 4.0f);
	if (GameHud)
	{
		GameHud->SetPlacementUIOpen(bOpen);
	}
}
