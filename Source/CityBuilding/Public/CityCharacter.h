
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CityCharacter.generated.h"

UCLASS()
class CITYBUILDING_API ACityCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ACityCharacter();
	// Called after the real C++ constructor is called
	ACityCharacter(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CameraComp;

	virtual void BeginPlay() override;

public:

	class USpringArmComponent* GetSpringArmComp() const { return SpringArmComp; }

};
