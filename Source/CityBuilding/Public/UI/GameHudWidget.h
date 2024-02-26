
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHudWidget.generated.h"

class UButton;
class UScrollBox;
class UPlaceableItemWidget;
class ACityHUD;

UCLASS()
class CITYBUILDING_API UGameHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UGameHudWidget(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY()
		ACityHUD* GameHud;

	UPROPERTY(meta = (BindWidget))
		UButton* OpenPlacementUIBtn;
	UPROPERTY(meta = (BindWidget))
		UScrollBox* PlaceablesScrollBox;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UPlaceableItemWidget> PlaceableItemWidgetTemplate;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* FadeOutOpenPlacementBtn;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* FadeInPlacementUI;

	void NativeConstruct() override;

public:

	UFUNCTION()
		void OpenPlacementUIBtnClicked();
		void TogglePlacementUI(const bool bOpen);

};
