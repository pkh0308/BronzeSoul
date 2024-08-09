// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/AI/BTTask_JumpAttack.h"
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

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UMutantAnimInstance> MyAnimInstance;

// Attack
protected:
	virtual void Attack() override;

// Jump Attack
protected:
	FOnJumpAttackFinished OnJumpAttackFinished;

	bool WaitingJumpAttack;
	bool OnJumpAttack;

	UPROPERTY(EditDefaultsOnly, category = "JumpAttack")
	float JumpAttackTime = 1.5f;

	UPROPERTY(VisibleAnywhere, category = "JumpAttack")
	TObjectPtr<AActor> JA_Target;

	UPROPERTY(VisibleAnywhere, category = "JumpAttack")
	FVector JA_TargetLoc;

	UPROPERTY(VisibleAnywhere, category = "JumpAttack")
	FVector JA_TargetDir;

public:
	bool IsWaitingJumpAttack();

	void BeginJumpAttack();

	void PlayJumpAttackAnim();

	void OnJumpBegin();
	void OnJumpEnd();

	void SetJumpAttackFinished(FOnJumpAttackFinished NewOnJumpAttackFinished);

	void EndJumpAttack();

// Die
protected:
	virtual void OnDie() override;
};
