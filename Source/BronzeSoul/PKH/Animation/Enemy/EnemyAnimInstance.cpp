// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/Enemy/EnemyAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/Enemy/EnemyBase.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Enemy = Cast<AEnemyBase>(GetOwningActor());
	if ( Enemy )
	{
		MoveComp = Enemy->GetCharacterMovement();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if ( nullptr == MoveComp )
	{
		return;
	}

	const FVector& Velocity = MoveComp->Velocity;

	bIsIdle = Velocity.Size2D() < WalkThreshold;
	bIsWalking = Velocity.Size2D() >= WalkThreshold;
	bIsRunning = Velocity.Size2D() > RunThreshold;
	bIsDead = Enemy->IsDead();
}
