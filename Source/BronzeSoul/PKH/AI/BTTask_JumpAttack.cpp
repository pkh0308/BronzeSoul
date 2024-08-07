// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTTask_JumpAttack.h"

#include "AIController.h"
#include "BTKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PKH/Enemy/EnemyBase.h"

EBTNodeResult::Type UBTTask_JumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult =  Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyBase* OwnerEnemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
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

	// 속도 조정
	OwnerEnemy->SetEnemyRun();

	// 사거리보다 타겟이 멀다면 달리기
	float JumpAttackDist = BBComp->GetValueAsFloat(KEY_JUMP_ATTACK_DIST);
	if(FVector::Dist(OwnerEnemy->GetActorLocation(), Player->GetActorLocation()) > JumpAttackDist)
	{
		OwnerEnemy->SetEnemyRun();

		/*FOnPasserAttackFinished OnAttakFinished;
		OnAttakFinished.BindLambda([&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});*/

		return EBTNodeResult::InProgress;
	}

	// 사거리 안에 있다면 점프 공격 실행
	// 애니메이션 완료 후에 종료 처리
	/*FOnPasserAttackFinished OnAttakFinished;
	OnAttakFinished.BindLambda([&]() 
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	});*/

	return EBTNodeResult::InProgress;
}
