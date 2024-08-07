// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Animation/Enemy/EnemyAnimInstance.h"
#include "MutantAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UMutantAnimInstance : public UEnemyAnimInstance
{
	GENERATED_BODY()

public:
	UMutantAnimInstance();

// Montages
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> Montage_JumpAttack;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> Montage_Die;

public:
	void PlayMontage_JumpAttack();
	void PlayMontage_Die();
};
