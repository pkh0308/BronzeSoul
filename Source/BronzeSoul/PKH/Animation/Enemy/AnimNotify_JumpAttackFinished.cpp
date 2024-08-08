// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/Enemy/AnimNotify_JumpAttackFinished.h"

#include "PKH/Enemy/Mutant/Enemy_Mutant.h"

void UAnimNotify_JumpAttackFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                            const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AEnemy_Mutant* Enemy = Cast<AEnemy_Mutant>(MeshComp->GetOwner());
	if( Enemy )
	{
		Enemy->EndJumpAttack();
	}
}
