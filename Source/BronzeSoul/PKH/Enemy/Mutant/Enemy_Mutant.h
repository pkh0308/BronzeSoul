// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Enemy/EnemyBase.h"
#include "Enemy_Mutant.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API AEnemy_Mutant : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemy_Mutant();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UMutantAnimInstance> AnimInstance;
};
