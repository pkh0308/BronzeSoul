// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/PaladinAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/Player/BSPlayerCharacter.h"

UPaladinAnimInstance::UPaladinAnimInstance()
{

}

void UPaladinAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<ABSPlayerCharacter>(GetOwningActor());
	if (Player)
	{
		MoveComp = Player->GetCharacterMovement();
	}
}

void UPaladinAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(nullptr == MoveComp)
	{
		return;
	}

	const FVector& Velocity = MoveComp->Velocity;

	bIsIdle = Velocity.Size2D() < WalkThreshold;
	bIsWalking = Velocity.Size2D() >= WalkThreshold;
	bIsRunning = Velocity.Size2D() > RunThreshold;
	bIsJumping = Velocity.Z > 0;
	bIsFalling = MoveComp->IsFalling();
}
