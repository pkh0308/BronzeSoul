﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_JumpAttack.generated.h"

DECLARE_DELEGATE(FOnJumpAttackFinished);

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UBTTask_JumpAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
