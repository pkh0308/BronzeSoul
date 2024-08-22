// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/Enemy/AnimNotify_MutantAttackEnd.h"

#include "MutantAnimInstance.h"
#include "PKH/Enemy/Mutant/Enemy_Mutant.h"

void UAnimNotify_MutantAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AEnemy_Mutant* Mutant = Cast<AEnemy_Mutant>(MeshComp->GetOwner());
	if ( nullptr == Mutant )
	{
		return;
	}

	UAnimInstance* Anim = Cast<UAnimInstance>(Mutant->GetMesh()->GetAnimInstance());
	if ( nullptr == Anim )
	{
		return;
	}

	UMutantAnimInstance* MutantAnim = Cast<UMutantAnimInstance>(Anim);
	if ( nullptr == MutantAnim )
	{
		return;
	}

	Mutant->SetNormalAttackColl(false, MutantAnim->IsLeftHand());
}
