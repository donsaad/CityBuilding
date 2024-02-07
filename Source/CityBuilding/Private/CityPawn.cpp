
#include "CityPawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACityPawn::ACityPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

ACityPawn::ACityPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	if (CollisionComp)
	{
		CollisionComp->InitSphereRadius(50.0f);
		CollisionComp->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
		CollisionComp->SetCanEverAffectNavigation(false);
		RootComponent = CollisionComp;
		MovementComp = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("MovementComp");
		if (MovementComp)
		{
			MovementComp->UpdatedComponent = CollisionComp;
		}
	}
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

void ACityPawn::BeginPlay()
{
	Super::BeginPlay();

}
