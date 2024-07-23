
#include "PKH/AI/BTTask_Attack.h"

#include "AIController.h"
#include "PKH/Enemy/EnemyBase.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if(nullptr == OwnerPawn)
	{
		return EBTNodeResult::Failed;
	}

	AEnemyBase* Enemy = Cast<AEnemyBase>(OwnerPawn);
	if(nullptr == Enemy)
	{
		return EBTNodeResult::Failed;
	}

	Enemy->Attack();
	return EBTNodeResult::Succeeded;
}
