// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UEnemyAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class AEnemyBase> Enemy;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCharacterMovementComponent> MoveComp;

// Flags
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsWalking : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsRunning : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsDead : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WalkThreshold = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RunThreshold = 250;
};
