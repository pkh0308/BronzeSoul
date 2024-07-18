// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/PaladinAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/Player/BSPlayerCharacter.h"

UPaladinAnimInstance::UPaladinAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_ComboMontageOneHandRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin/Blueprint/AM_AttackOneHand.AM_AttackOneHand'"));
	if(AM_ComboMontageOneHandRef.Object)
	{
		AM_ComboMontageOneHand = AM_ComboMontageOneHandRef.Object;
	}
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

#pragma region Combo
void UPaladinAnimInstance::PlayMontage_Combo(int32 Idx)
{
	if(Idx == 1)
	{
		Montage_Play(AM_ComboMontageOneHand);
	}
	else
	{
		FName NextCombo(FString::Printf(TEXT("Combo_%d"), Idx));
		Montage_JumpToSection(NextCombo);
	}
}
#pragma endregion