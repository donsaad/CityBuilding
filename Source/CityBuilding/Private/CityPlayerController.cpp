
#include "CityPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "CityCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "CityHUD.h"
#include "BuilderSubsystem.h"

ACityPlayerController::ACityPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CameraRotationSpeed = 5.0f;
	CameraZoomSpeed = 50.0f;
	CameraMinZoom = 200.0f;
	CameraMaxZoom = 2200.0f;
	CameraAngleMinClamp = 300.0f;
	CameraAngleMaxClamp = 359.0f;

	bMiddleMouseIsPressed = false;

	bEnableClickEvents = true;
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
}

void ACityPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &ACityPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ACityPlayerController::MoveRight);
		InputComponent->BindAxis("Scroll", this, &ACityPlayerController::HandleMouseScroll);
		InputComponent->BindAxis("MouseX", this, &ACityPlayerController::MouseMoveX);
		InputComponent->BindAxis("MouseY", this, &ACityPlayerController::MouseMoveY);
		InputComponent->BindAction("MiddleMouseClick", IE_Pressed, this, &ACityPlayerController::ToggleMiddleMouseClick);
		InputComponent->BindAction("MiddleMouseClick", IE_Released, this, &ACityPlayerController::ToggleMiddleMouseClick);
		InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &ACityPlayerController::HandleRightMouseClick);
		InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ACityPlayerController::HandleLeftMouseClick);
		InputComponent->BindAction("PressE", IE_Pressed, this, &ACityPlayerController::EKeyPressed);
		InputComponent->BindAction("PressQ", IE_Pressed, this, &ACityPlayerController::QKeyPressed);
	}
}

void ACityPlayerController::RotateCamera(float Value)
{
	AddYawInput(Value * CameraRotationSpeed);
}

void ACityPlayerController::MoveForward(float Value)
{
	if (CityCharacter)
	{
		// moving forward in the same direction as the control rotation
		FVector WorldDir = FRotator(0.0f, GetControlRotation().Yaw, 0.0f).Vector();
		CityCharacter->AddMovementInput(WorldDir, Value);
	}
}

void ACityPlayerController::MoveRight(float Value)
{
	if (CityCharacter)
	{
		const FVector WorldDir = UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, 0.f));
		CityCharacter->AddMovementInput(WorldDir, Value);
	}
}

void ACityPlayerController::HandleMouseScroll(float Value)
{
	if (CityCharacter && CityCharacter->GetSpringArmComp())
	{
		Value *= CameraZoomSpeed;
		Value += CityCharacter->GetSpringArmComp()->TargetArmLength;
		Value = FMath::Clamp(Value, CameraMinZoom, CameraMaxZoom);
		CityCharacter->GetSpringArmComp()->TargetArmLength = Value;
	}
}

void ACityPlayerController::MouseMoveX(float Value)
{
	// handle camera rotation
	if (bMiddleMouseIsPressed && CityCharacter)
	{
		AddYawInput(Value * CameraRotationSpeed);
	}
	//TODO: signal Builder that mouse is moving in X
}

void ACityPlayerController::MouseMoveY(float Value)
{
	// handle camera pitch changes
	if (bMiddleMouseIsPressed && CityCharacter)
	{
		if (USpringArmComponent* SpringArmComp = CityCharacter->GetSpringArmComp())
		{
			Value *= CameraRotationSpeed;
			Value += SpringArmComp->GetComponentRotation().Pitch;
			Value = FMath::ClampAngle(Value, CameraAngleMinClamp, CameraAngleMaxClamp);
			SpringArmComp->SetWorldRotation(FRotator(Value, SpringArmComp->GetComponentRotation().Yaw, SpringArmComp->GetComponentRotation().Roll));
		}
	}
	//TODO signal Builder that mouse is moving in Y
}


void ACityPlayerController::ToggleMiddleMouseClick()
{
	bMiddleMouseIsPressed = !bMiddleMouseIsPressed;
}

void ACityPlayerController::HandleRightMouseClick()
{
	if (Builder && Builder->IsPlacementModeEnabled())
	{
		Builder->CancelPlaceBuilding();
	}
	else if (ACityHUD* Hud = GetHUD<ACityHUD>())
	{
		if (Hud->IsPlacementUIOpen())
		{
			Hud->ClosePlacementUI();
		}
	}
}

void ACityPlayerController::HandleLeftMouseClick()
{
	if (Builder)
	{
		Builder->PlaceBuilding();
	}
}

void ACityPlayerController::EKeyPressed()
{
	if (Builder)
	{
		Builder->RotateBuilding(90.0f);
	}
}

void ACityPlayerController::QKeyPressed()
{
	if (Builder)
	{
		Builder->RotateBuilding(-90.0f);
	}
}

void ACityPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	// to avoid casting in input methods and improve performance a bit
	CityCharacter = GetPawn<ACityCharacter>();
	// hold a reference to the BuilderSubsystem
	if (UGameInstance* GI = GetGameInstance())
	{
		Builder = GI->GetSubsystem<UBuilderSubsystem>();
	}
}