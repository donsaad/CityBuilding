
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CityPawn.generated.h"

UCLASS()
class CITYBUILDING_API ACityPawn : public APawn
{
	GENERATED_BODY()

public:
	ACityPawn();
	ACityPawn(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
		class UPawnMovementComponent* MovementComp;
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CameraComp;

	virtual void BeginPlay() override;

public:

	//virtual void Tick(float DeltaTime) override;

};
