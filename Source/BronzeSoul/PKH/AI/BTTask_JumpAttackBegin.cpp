// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTTask_JumpAttackBegin.h"

#include "PKH/Enemy/Mutant/Enemy_Mutant.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_JumpAttackBegin::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy_Mutant* Enemy = Cast<AEnemy_Mutant>(OwnerComp.GetAIOwner()->GetPawn());
	if(nullptr == Enemy)
	{
		return EBTNodeResult::Failed;
	}

	Enemy->BeginJumpAttack();
	return EBTNodeResult::Succeeded;
}
