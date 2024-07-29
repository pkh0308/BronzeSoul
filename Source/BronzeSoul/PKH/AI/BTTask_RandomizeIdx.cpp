// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTTask_RandomizeIdx.h"

#include "BTKey.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RandomizeIdx::UBTTask_RandomizeIdx()
{

}

EBTNodeResult::Type UBTTask_RandomizeIdx::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if(nullptr == BBComp)
	{
		return EBTNodeResult::Failed;
	}

	int32 MaxIdx = BBComp->GetValueAsInt(KEY_MAX_IDX);
	BBComp->SetValueAsInt(KEY_RAND_IDX, FMath::RandRange(0, MaxIdx));
	return EBTNodeResult::Succeeded;
}
