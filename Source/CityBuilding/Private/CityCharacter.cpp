
#include "CityCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACityCharacter::ACityCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

ACityCharacter::ACityCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	if (SpringArmComp)
	{
		SpringArmComp->SetupAttachment(RootComponent);

		CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
		if (CameraComp)
		{
			CameraComp->SetupAttachment(SpringArmComp);
		}
	}
}

void ACityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
