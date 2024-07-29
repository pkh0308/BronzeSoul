// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTDecorator_CheckRandIdx.h"

#include "BTKey.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckRandIdx::UBTDecorator_CheckRandIdx()
{
	NodeName = TEXT("Idx_0");
}

bool UBTDecorator_CheckRandIdx::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool SuperResult =  Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if(nullptr == BBComp)
	{
		return false;
	}

	return BBComp->GetValueAsInt(KEY_RAND_IDX) == TargetIdx;
}
