
#include "CityHUD.h"
#include "Blueprint/UserWidget.h"

ACityHUD::ACityHUD()
{

}

ACityHUD::ACityHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsPlacementUIOpen = false;
}

void ACityHUD::ClosePlacementUI_Implementation()
{
	bIsPlacementUIOpen = false;
}

void ACityHUD::BeginPlay()
{
	Super::BeginPlay();
	//if (HudTemplate)
	//{
	//	GameHudWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), HudTemplate);
	//	if (GameHudWidget)
	//	{
	//		GameHudWidget->AddToViewport();
	//	}
	//}
}
