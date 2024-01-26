
#include "VisitorAIController.h"

void AVisitorAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* TempBlackboard = Blackboard.Get();
	UseBlackboard(BlackboardAsset, TempBlackboard);

	RunBehaviorTree(BTAsset);
}
