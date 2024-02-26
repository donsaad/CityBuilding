
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlaceableItemWidget.generated.h"

enum class EBuildingType : uint8;
class UButton;
class UTextBlock;

UCLASS()
class CITYBUILDING_API UPlaceableItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPlaceableItemWidget(const FObjectInitializer& ObjectInitializer);
	void SetType(const EBuildingType BuildingType);

protected:

	UPROPERTY(meta = (BindWidget))
		UButton* ItemButton;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ItemNameText;

	EBuildingType ItemType;

	void NativeConstruct() override;

	UFUNCTION()
		void ItemButtonClicked();

};
