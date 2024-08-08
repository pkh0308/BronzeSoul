// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTTask_JumpAttack.h"

#include "AIController.h"
#include "BTKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PKH/Enemy/Mutant/Enemy_Mutant.h"

EBTNodeResult::Type UBTTask_JumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult =  Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy_Mutant* OwnerEnemy = Cast<AEnemy_Mutant>(OwnerComp.GetAIOwner()->GetPawn());
	if ( nullptr == OwnerEnemy )
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if ( nullptr == BBComp )
	{
		return EBTNodeResult::Failed;
	}

	AActor* Player = Cast<AActor>(BBComp->GetValueAsObject(KEY_PLAYER));
	if(nullptr == Player)
	{
		return EBTNodeResult::Failed;
	}

	// 애니메이션 완료 후에 종료하도록 InProgress 반환
	// 실제 종료 처리는 AnimNotify를 통해 실행
	OwnerEnemy->PlayJumpAttackAnim();

	FOnJumpAttackFinished OnJumpAttackFinished;
	OnJumpAttackFinished.BindLambda([&]()
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	});

	OwnerEnemy->SetJumpAttackFinished(OnJumpAttackFinished);
	return EBTNodeResult::InProgress;
}
