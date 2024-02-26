
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CityHUD.generated.h"

class UUserWidget;
class UGameHudWidget;

UCLASS()
class CITYBUILDING_API ACityHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACityHUD();
	ACityHUD(const FObjectInitializer& ObjectInitializer);
	bool IsPlacementUIOpen() const { return bIsPlacementUIOpen; }

	void ClosePlacementUI();
	void SetPlacementUIOpen(const bool bOpened) { bIsPlacementUIOpen = bOpened; }
protected:

	UPROPERTY(BlueprintReadWrite)
		UGameHudWidget* GameHudWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UGameHudWidget> HudTemplate;

	UPROPERTY(BlueprintReadWrite)
		bool bIsPlacementUIOpen;

	void BeginPlay() override;
};
