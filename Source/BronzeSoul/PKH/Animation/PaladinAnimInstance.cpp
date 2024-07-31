// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/PaladinAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/Player/BSPlayerCharacter.h"

UPaladinAnimInstance::UPaladinAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_ComboMontageOneHandRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin_RootAdded/Blueprint/AM_Attack.AM_Attack'"));
	if(AM_ComboMontageOneHandRef.Object)
	{
		AM_ComboMontageOneHand = AM_ComboMontageOneHandRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DodgeRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin_RootAdded/Blueprint/AM_Dodge.AM_Dodge'"));
	if ( AM_DodgeRef.Object )
	{
		AM_Dodge = AM_DodgeRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GuardRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin_RootAdded/Blueprint/AM_Guard.AM_Guard'"));
	if ( AM_GuardRef.Object )
	{
		AM_Guard = AM_GuardRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DieRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin_RootAdded/Blueprint/AM_Die.AM_Die'"));
	if ( AM_DieRef.Object )
	{
		AM_Die = AM_DieRef.Object;
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
	bOnGuard = Player->OnGuardNow();
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

void UPaladinAnimInstance::PlayMontage_Dodge()
{
	Montage_Play(AM_Dodge);
}

void UPaladinAnimInstance::PlayMontage_Guard()
{
	if(bOnGuard)
	{
		Montage_Play(AM_Guard);
	}
	else
	{
		Montage_Play(AM_Guard);
		Montage_JumpToSection(GuardOff);
	}
}

void UPaladinAnimInstance::PlayMontage_Die()
{
	Montage_Play(AM_Die);
}
