
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_NotifyReachedDest.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API UBTT_NotifyReachedDest : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
