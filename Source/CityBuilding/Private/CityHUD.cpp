
#include "CityHUD.h"
#include "Blueprint/UserWidget.h"
#include <UI/GameHudWidget.h>

ACityHUD::ACityHUD()
{

}

ACityHUD::ACityHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIsPlacementUIOpen(false)
{

}

void ACityHUD::ClosePlacementUI()
{
	bIsPlacementUIOpen = false;
	if (GameHudWidget)
	{
		GameHudWidget->TogglePlacementUI(false);
	}
}

void ACityHUD::BeginPlay()
{
	Super::BeginPlay();
	if (HudTemplate)
	{
		GameHudWidget = CreateWidget<UGameHudWidget>(GetOwningPlayerController(), HudTemplate);
		if (GameHudWidget)
		{
			GameHudWidget->AddToViewport();
		}
	}
}
