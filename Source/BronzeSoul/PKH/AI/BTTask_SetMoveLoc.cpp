// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTTask_SetMoveLoc.h"

#include "AIController.h"
#include "BTKey.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetMoveLoc::UBTTask_SetMoveLoc()
{

}

EBTNodeResult::Type UBTTask_SetMoveLoc::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if(nullptr == OwnerPawn)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (nullptr == BBComp)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	const FVector& OriginLoc = OwnerPawn->GetActorLocation();
	float PatrolRadius = BBComp->GetValueAsFloat(KEY_PATROL_DIST);
	FNavLocation NextLoc;
	if(NavSystem->GetRandomReachablePointInRadius(OriginLoc, PatrolRadius,NextLoc))
	{
		BBComp->SetValueAsVector(KEY_PATROL_LOC, NextLoc.Location);
		return EBTNodeResult::Succeeded;
	}

	return SuperResult;
}
