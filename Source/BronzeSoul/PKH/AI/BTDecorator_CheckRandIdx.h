// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckRandIdx.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UBTDecorator_CheckRandIdx : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckRandIdx();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 TargetIdx = 0;
};
