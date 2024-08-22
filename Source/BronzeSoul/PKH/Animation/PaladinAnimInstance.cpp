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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DamagedRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin_RootAdded/Blueprint/AM_Damaged.AM_Damaged'"));
	if ( AM_DamagedRef.Object )
	{
		AM_Damaged = AM_DamagedRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_KnockDownRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin_RootAdded/Blueprint/AM_KnockDown.AM_KnockDown'"));
	if ( AM_KnockDownRef.Object )
	{
		AM_KnockDown = AM_KnockDownRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StandUpRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin_RootAdded/Blueprint/AM_StandUp.AM_StandUp'"));
	if ( AM_StandUpRef.Object )
	{
		AM_StandUp = AM_StandUpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DieRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Paladin_RootAdded/Blueprint/AM_Die.AM_Die'"));
	if ( AM_DieRef.Object )
	{
		AM_Die = AM_DieRef.Object;
	}

	// Texts
	DamagedSections.Add(TEXT("Damaged_1"));
	DamagedSections.Add(TEXT("Damaged_2"));
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
	bIsDead = Player->IsDead();
	bOnGuard = Player->OnGuardNow();

	// 방향
	const FVector& DirVec = Player->GetDirectionVec();
	if(DirVec.Y != 0)
	{
		PlayerDir = DirVec.Y > 0 ? EPlayerDir::Right : EPlayerDir::Left;
	}
	else
	{
		PlayerDir = DirVec.X > 0 ? EPlayerDir::Forward : EPlayerDir::Backward;
	}
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

#pragma region Montage
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

void UPaladinAnimInstance::PlayMontage_Damaged()
{
	// 몽타주 내 랜덤 애니메이션 재생
	const int32 RandIdx = FMath::RandRange(0, 1);
	Montage_Play(AM_Damaged);
	Montage_JumpToSection(DamagedSections[RandIdx]);
}

void UPaladinAnimInstance::PlayMontage_KnockDown()
{
	Montage_Play(AM_KnockDown);
}

void UPaladinAnimInstance::PlayMontage_StandUp()
{
	Montage_Play(AM_StandUp);
}

void UPaladinAnimInstance::PlayMontage_Die()
{
	Montage_Play(AM_Die);
}
#pragma endregion

