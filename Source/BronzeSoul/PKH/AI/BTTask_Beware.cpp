// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/BTTask_Beware.h"

UBTTask_Beware::UBTTask_Beware()
{
}

EBTNodeResult::Type UBTTask_Beware::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult =  Super::ExecuteTask(OwnerComp, NodeMemory);


	return SuperResult;
}
