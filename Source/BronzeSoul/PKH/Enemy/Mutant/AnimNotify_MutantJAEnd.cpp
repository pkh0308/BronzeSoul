// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Enemy/Mutant/AnimNotify_MutantJAEnd.h"

#include "Enemy_Mutant.h"

void UAnimNotify_MutantJAEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AEnemy_Mutant* Mutant = Cast<AEnemy_Mutant>(MeshComp->GetOwner());
	if ( Mutant )
	{
		Mutant->SetJumpAttackColl(false);
	}
}
