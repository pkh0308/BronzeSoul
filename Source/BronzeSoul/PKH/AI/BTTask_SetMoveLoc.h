// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetMoveLoc.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UBTTask_SetMoveLoc : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SetMoveLoc();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
