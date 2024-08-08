// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/Enemy/MutantAnimInstance.h"

#include "PKH/Enemy/Mutant/Enemy_Mutant.h"

UMutantAnimInstance::UMutantAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_AttackRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Mutant/Blueprint/AM_Attack.AM_Attack'"));
	if ( Montage_AttackRef.Object )
	{
		Montage_Attack = Montage_AttackRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_JumpAttackRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Mutant/Blueprint/AM_JumpAttack.AM_JumpAttack'"));
	if( Montage_JumpAttackRef.Object )
	{
		Montage_JumpAttack = Montage_JumpAttackRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_DieRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Character/Mutant/Blueprint/AM_Die.AM_Die'"));
	if ( Montage_DieRef.Object )
	{
		Montage_Die = Montage_DieRef.Object;
	}
}

void UMutantAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Mutant = Cast<AEnemy_Mutant>(GetOwningActor());
}

void UMutantAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(nullptr == MoveComp)
	{
		return;
	}

	bIsWaitingJumpAttack = Mutant->IsDoingJumpAttack();
}

#pragma region Montage
void UMutantAnimInstance::PlayMontage_Attack()
{
	Montage_Play(Montage_Attack);
}

void UMutantAnimInstance::PlayMontage_JumpAttack()
{
	Montage_Play(Montage_JumpAttack);
}

void UMutantAnimInstance::PlayMontage_Die()
{
	Montage_Play(Montage_Die);
}
#pragma endregion
