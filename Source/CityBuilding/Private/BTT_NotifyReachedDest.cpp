
#include "BTT_NotifyReachedDest.h"
#include "CityGameModeBase.h"
#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UBTT_NotifyReachedDest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetAIOwner())
	{
		if (UWorld* World = GetWorld())
		{
			if (ACityGameModeBase* GM = World->GetAuthGameMode<ACityGameModeBase>())
			{
				GM->NotifyVisitorReachedDestination(OwnerComp.GetAIOwner()->GetPawn<ACharacter>());
			}
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
