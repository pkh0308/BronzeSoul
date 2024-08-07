// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/Enemy/MutantAnimInstance.h"

UMutantAnimInstance::UMutantAnimInstance()
{
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

#pragma region Montage
void UMutantAnimInstance::PlayMontage_JumpAttack()
{
	Montage_Play(Montage_JumpAttack);
}

void UMutantAnimInstance::PlayMontage_Die()
{
	Montage_Play(Montage_Die);
}
#pragma endregion
