// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTTask_SetEnemyWalk.h"

#include "PKH/Enemy/EnemyBase.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_SetEnemyWalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SueprResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyBase* OwnEnemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if(nullptr == OwnEnemy )
	{
		return EBTNodeResult::Failed;
	}

	OwnEnemy->SetEnemyWalk();
	return EBTNodeResult::Succeeded;
}
