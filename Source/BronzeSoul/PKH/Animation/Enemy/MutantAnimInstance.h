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

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class AEnemy_Mutant> Mutant;

// Flag
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsWaitingJumpAttack : 1;

// Montages
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> Montage_Attack;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> Montage_JumpAttack;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> Montage_Damaged;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> Montage_Die;

public:
	void PlayMontage_Attack();
	void PlayMontage_JumpAttack();
	void PlayMontage_Damaged();
	void PlayMontage_Die();

// Section Check
protected:
	UPROPERTY(EditDefaultsOnly)
	FName MontageSection_Combo2 = TEXT("Combo_2");

public:
	bool IsLeftHand() const;
};
