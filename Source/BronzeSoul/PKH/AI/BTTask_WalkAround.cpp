// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTTask_WalkAround.h"

#include "AIController.h"
#include "BTKey.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PKH/Enemy/EnemyBase.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_WalkAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult =  Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyBase* OwnerEnemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if(nullptr == OwnerEnemy )
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if(nullptr == BBComp)
	{
		return EBTNodeResult::Failed;
	}

	// 방향 회전
	AActor* Target = Cast<AActor>(BBComp->GetValueAsObject(KEY_PLAYER));
	if(nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}
	FVector DirVec = ( Target->GetActorLocation() - OwnerEnemy->GetActorLocation() ).GetSafeNormal2D();
	OwnerEnemy->SetActorRotation(DirVec.ToOrientationRotator());

	// 속도 조정
	OwnerEnemy->SetEnemyWalk();

	// 이동 위치 설정
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerEnemy->GetActorLocation();
	float RotateRadius = 50.0f;
	FNavLocation ResultLoc;
	if(NavSystem->GetRandomPointInNavigableRadius(Origin, RotateRadius, ResultLoc))
	{
		BBComp->SetValueAsVector(KEY_PATROL_LOC, ResultLoc.Location); UE_LOG(LogTemp, Log, TEXT("UBTTask_WalkAround"));
	}

	return EBTNodeResult::Succeeded;
}
