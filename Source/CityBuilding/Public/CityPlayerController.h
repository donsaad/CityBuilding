
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CityPlayerController.generated.h"

UCLASS()
class CITYBUILDING_API ACityPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACityPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	// Scale camera turn speed
	UPROPERTY(EditDefaultsOnly, Category = "Camera Tuneables")
		float CameraRotationSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Tuneables")
		float CameraZoomSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Tuneables")
		float CameraMinZoom;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Tuneables")
		float CameraMaxZoom;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Tuneables")
		float CameraPitchScale;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Tuneables")
		float CameraYawScale;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Tuneables")
		float CameraAngleMinClamp;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Tuneables")
		float CameraAngleMaxClamp;

	bool bMiddleMouseIsPressed;

	UPROPERTY()
		class ACityCharacter* CityCharacter;
	UPROPERTY()
		class UBuilderSubsystem* Builder;

	virtual void SetupInputComponent() override;
	void SetPawn(APawn* InPawn) final;

	void RotateCamera(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);
	void HandleMouseScroll(float Value);
	void MouseMoveX(float Value);
	void MouseMoveY(float Value);
	void ToggleMiddleMouseClick();
	void HandleRightMouseClick();
	void HandleLeftMouseClick();
	void EKeyPressed();
	void QKeyPressed();
};
