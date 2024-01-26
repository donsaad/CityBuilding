
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VisitorAIController.generated.h"


UCLASS()
class CITYBUILDING_API AVisitorAIController : public AAIController
{
	GENERATED_BODY()

public:

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree Setup")
		UBlackboardData* BlackboardAsset;
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree Setup")
		UBehaviorTree* BTAsset;

	void OnPossess(APawn* InPawn) override;
	
};
