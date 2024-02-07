
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CityHUD.generated.h"

class UUserWidget;

UCLASS()
class CITYBUILDING_API ACityHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACityHUD();
	ACityHUD(const FObjectInitializer& ObjectInitializer);
	bool IsPlacementUIOpen() const { return bIsPlacementUIOpen; }

	UFUNCTION(BlueprintNativeEvent)
		void ClosePlacementUI();
	UFUNCTION(BlueprintCallable)
		void SetPlacementUIOpen(bool bOpened) { bIsPlacementUIOpen = bOpened; }
protected:

	//UPROPERTY(BlueprintReadWrite)
		//UUserWidget* GameHudWidget;

	//UPROPERTY(EditDefaultsOnly)
	//	TSubclassOf<UUserWidget> HudTemplate;

	UPROPERTY(BlueprintReadWrite)
		bool bIsPlacementUIOpen;

	void BeginPlay() override;
};
